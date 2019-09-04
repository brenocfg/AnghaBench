#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_3__ {int steps; int size; } ;
struct nand_chip {TYPE_1__ ecc; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct mtd_info {int writesize; TYPE_2__ dev; } ;
struct lpc32xx_nand_host {int* data_buf; int* ecc_buf; int /*<<< orphan*/  io_base; int /*<<< orphan*/  dma_chan; int /*<<< orphan*/  io_base_dma; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;

/* Variables and functions */
 int DMA_DEV_TO_MEM ; 
 int DMA_MEM_TO_DEV ; 
 int EIO ; 
 int /*<<< orphan*/  LPC32XX_DMA_TIMEOUT ; 
 int SLCCFG_DMA_BURST ; 
 int SLCCFG_DMA_DIR ; 
 int SLCCFG_DMA_ECC ; 
 int SLCCFG_ECC_EN ; 
 int SLCCTRL_DMA_START ; 
 int SLCCTRL_ECC_CLEAR ; 
 int SLCSTAT_DMA_FIFO ; 
 int /*<<< orphan*/  SLC_CFG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLC_CTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLC_DMA_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLC_ECC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLC_STAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLC_TC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ ) ; 
 void* high_memory ; 
 unsigned long jiffies ; 
 int lpc32xx_xmit_dma (struct mtd_info*,int /*<<< orphan*/ ,int*,int,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct lpc32xx_nand_host* nand_get_controller_data (struct nand_chip*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpc32xx_xfer(struct mtd_info *mtd, uint8_t *buf, int eccsubpages,
			int read)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct lpc32xx_nand_host *host = nand_get_controller_data(chip);
	int i, status = 0;
	unsigned long timeout;
	int res;
	enum dma_transfer_direction dir =
		read ? DMA_DEV_TO_MEM : DMA_MEM_TO_DEV;
	uint8_t *dma_buf;
	bool dma_mapped;

	if ((void *)buf <= high_memory) {
		dma_buf = buf;
		dma_mapped = true;
	} else {
		dma_buf = host->data_buf;
		dma_mapped = false;
		if (!read)
			memcpy(host->data_buf, buf, mtd->writesize);
	}

	if (read) {
		writel(readl(SLC_CFG(host->io_base)) |
		       SLCCFG_DMA_DIR | SLCCFG_ECC_EN | SLCCFG_DMA_ECC |
		       SLCCFG_DMA_BURST, SLC_CFG(host->io_base));
	} else {
		writel((readl(SLC_CFG(host->io_base)) |
			SLCCFG_ECC_EN | SLCCFG_DMA_ECC | SLCCFG_DMA_BURST) &
		       ~SLCCFG_DMA_DIR,
			SLC_CFG(host->io_base));
	}

	/* Clear initial ECC */
	writel(SLCCTRL_ECC_CLEAR, SLC_CTRL(host->io_base));

	/* Transfer size is data area only */
	writel(mtd->writesize, SLC_TC(host->io_base));

	/* Start transfer in the NAND controller */
	writel(readl(SLC_CTRL(host->io_base)) | SLCCTRL_DMA_START,
	       SLC_CTRL(host->io_base));

	for (i = 0; i < chip->ecc.steps; i++) {
		/* Data */
		res = lpc32xx_xmit_dma(mtd, SLC_DMA_DATA(host->io_base_dma),
				       dma_buf + i * chip->ecc.size,
				       mtd->writesize / chip->ecc.steps, dir);
		if (res)
			return res;

		/* Always _read_ ECC */
		if (i == chip->ecc.steps - 1)
			break;
		if (!read) /* ECC availability delayed on write */
			udelay(10);
		res = lpc32xx_xmit_dma(mtd, SLC_ECC(host->io_base_dma),
				       &host->ecc_buf[i], 4, DMA_DEV_TO_MEM);
		if (res)
			return res;
	}

	/*
	 * According to NXP, the DMA can be finished here, but the NAND
	 * controller may still have buffered data. After porting to using the
	 * dmaengine DMA driver (amba-pl080), the condition (DMA_FIFO empty)
	 * appears to be always true, according to tests. Keeping the check for
	 * safety reasons for now.
	 */
	if (readl(SLC_STAT(host->io_base)) & SLCSTAT_DMA_FIFO) {
		dev_warn(mtd->dev.parent, "FIFO not empty!\n");
		timeout = jiffies + msecs_to_jiffies(LPC32XX_DMA_TIMEOUT);
		while ((readl(SLC_STAT(host->io_base)) & SLCSTAT_DMA_FIFO) &&
		       time_before(jiffies, timeout))
			cpu_relax();
		if (!time_before(jiffies, timeout)) {
			dev_err(mtd->dev.parent, "FIFO held data too long\n");
			status = -EIO;
		}
	}

	/* Read last calculated ECC value */
	if (!read)
		udelay(10);
	host->ecc_buf[chip->ecc.steps - 1] =
		readl(SLC_ECC(host->io_base));

	/* Flush DMA */
	dmaengine_terminate_all(host->dma_chan);

	if (readl(SLC_STAT(host->io_base)) & SLCSTAT_DMA_FIFO ||
	    readl(SLC_TC(host->io_base))) {
		/* Something is left in the FIFO, something is wrong */
		dev_err(mtd->dev.parent, "DMA FIFO failure\n");
		status = -EIO;
	}

	/* Stop DMA & HW ECC */
	writel(readl(SLC_CTRL(host->io_base)) & ~SLCCTRL_DMA_START,
	       SLC_CTRL(host->io_base));
	writel(readl(SLC_CFG(host->io_base)) &
	       ~(SLCCFG_DMA_DIR | SLCCFG_ECC_EN | SLCCFG_DMA_ECC |
		 SLCCFG_DMA_BURST), SLC_CFG(host->io_base));

	if (!dma_mapped && read)
		memcpy(buf, host->data_buf, mtd->writesize);

	return status;
}