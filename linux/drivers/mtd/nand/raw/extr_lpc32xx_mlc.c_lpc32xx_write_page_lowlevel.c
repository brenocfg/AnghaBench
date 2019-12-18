#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct nand_chip {int /*<<< orphan*/ * oob_poi; } ;
struct mtd_info {int /*<<< orphan*/  writesize; } ;
struct lpc32xx_nand_host {int mlcsubpages; int /*<<< orphan*/  io_base; int /*<<< orphan*/ * dma_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  MLC_BUFF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLC_ECC_AUTO_ENC_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLC_ECC_ENC_REG (int /*<<< orphan*/ ) ; 
 void* high_memory ; 
 int /*<<< orphan*/  lpc32xx_waitfunc_controller (struct nand_chip*) ; 
 int lpc32xx_xmit_dma (struct mtd_info*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 struct lpc32xx_nand_host* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  nand_prog_page_begin_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nand_prog_page_end_op (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 scalar_t__ use_dma ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpc32xx_write_page_lowlevel(struct nand_chip *chip,
				       const uint8_t *buf, int oob_required,
				       int page)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct lpc32xx_nand_host *host = nand_get_controller_data(chip);
	const uint8_t *oobbuf = chip->oob_poi;
	uint8_t *dma_buf = (uint8_t *)buf;
	int res;
	int i, j;

	if (use_dma && (void *)buf >= high_memory) {
		dma_buf = host->dma_buf;
		memcpy(dma_buf, buf, mtd->writesize);
	}

	nand_prog_page_begin_op(chip, page, 0, NULL, 0);

	for (i = 0; i < host->mlcsubpages; i++) {
		/* Start Encode */
		writeb(0x00, MLC_ECC_ENC_REG(host->io_base));

		/* Write 512 + 6 Bytes to Buffer */
		if (use_dma) {
			res = lpc32xx_xmit_dma(mtd, dma_buf + i * 512, 512,
					       DMA_MEM_TO_DEV);
			if (res)
				return res;
		} else {
			for (j = 0; j < (512 >> 2); j++) {
				writel(*((uint32_t *)(buf)),
				       MLC_BUFF(host->io_base));
				buf += 4;
			}
		}
		writel(*((uint32_t *)(oobbuf)), MLC_BUFF(host->io_base));
		oobbuf += 4;
		writew(*((uint16_t *)(oobbuf)), MLC_BUFF(host->io_base));
		oobbuf += 12;

		/* Auto Encode w/ Bit 8 = 0 (see LPC MLC Controller manual) */
		writeb(0x00, MLC_ECC_AUTO_ENC_REG(host->io_base));

		/* Wait for Controller Ready */
		lpc32xx_waitfunc_controller(chip);
	}

	return nand_prog_page_end_op(chip);
}