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
struct sunxi_nfc {int /*<<< orphan*/  dev; scalar_t__ regs; int /*<<< orphan*/  dmac; } ;
struct scatterlist {int dummy; } ;
struct nand_chip {int /*<<< orphan*/  controller; } ;
struct mtd_info {int dummy; } ;
struct dma_async_tx_descriptor {int dummy; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  dma_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CTRL_ACK ; 
 int DMA_DEV_TO_MEM ; 
 int DMA_FROM_DEVICE ; 
 int DMA_MEM_TO_DEV ; 
 int EINVAL ; 
 int ENOMEM ; 
 int NFC_RAM_METHOD ; 
 scalar_t__ NFC_REG_CNT ; 
 scalar_t__ NFC_REG_CTL ; 
 scalar_t__ NFC_REG_SECTOR_NUM ; 
 int dma_map_sg (int /*<<< orphan*/ ,struct scatterlist*,int,int) ; 
 int dma_submit_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,struct scatterlist*,int,int) ; 
 struct dma_async_tx_descriptor* dmaengine_prep_slave_sg (int /*<<< orphan*/ ,struct scatterlist*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,void const*,int) ; 
 struct sunxi_nfc* to_sunxi_nfc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int sunxi_nfc_dma_op_prepare(struct mtd_info *mtd, const void *buf,
				    int chunksize, int nchunks,
				    enum dma_data_direction ddir,
				    struct scatterlist *sg)
{
	struct nand_chip *nand = mtd_to_nand(mtd);
	struct sunxi_nfc *nfc = to_sunxi_nfc(nand->controller);
	struct dma_async_tx_descriptor *dmad;
	enum dma_transfer_direction tdir;
	dma_cookie_t dmat;
	int ret;

	if (ddir == DMA_FROM_DEVICE)
		tdir = DMA_DEV_TO_MEM;
	else
		tdir = DMA_MEM_TO_DEV;

	sg_init_one(sg, buf, nchunks * chunksize);
	ret = dma_map_sg(nfc->dev, sg, 1, ddir);
	if (!ret)
		return -ENOMEM;

	dmad = dmaengine_prep_slave_sg(nfc->dmac, sg, 1, tdir, DMA_CTRL_ACK);
	if (!dmad) {
		ret = -EINVAL;
		goto err_unmap_buf;
	}

	writel(readl(nfc->regs + NFC_REG_CTL) | NFC_RAM_METHOD,
	       nfc->regs + NFC_REG_CTL);
	writel(nchunks, nfc->regs + NFC_REG_SECTOR_NUM);
	writel(chunksize, nfc->regs + NFC_REG_CNT);
	dmat = dmaengine_submit(dmad);

	ret = dma_submit_error(dmat);
	if (ret)
		goto err_clr_dma_flag;

	return 0;

err_clr_dma_flag:
	writel(readl(nfc->regs + NFC_REG_CTL) & ~NFC_RAM_METHOD,
	       nfc->regs + NFC_REG_CTL);

err_unmap_buf:
	dma_unmap_sg(nfc->dev, sg, 1, ddir);
	return ret;
}