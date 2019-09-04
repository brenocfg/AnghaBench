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
typedef  int /*<<< orphan*/  u8 ;
struct sunxi_nfc {int /*<<< orphan*/  dmac; scalar_t__ regs; } ;
struct scatterlist {int dummy; } ;
struct nand_ecc_ctrl {int steps; int bytes; int /*<<< orphan*/  size; } ;
struct nand_chip {int options; int /*<<< orphan*/ * oob_poi; struct nand_ecc_ctrl ecc; int /*<<< orphan*/  controller; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int NAND_CMD_PAGEPROG ; 
 int NAND_CMD_RNDIN ; 
 int NAND_NEED_SCRAMBLING ; 
 int NFC_ACCESS_DIR ; 
 int /*<<< orphan*/  NFC_CMD_INT_FLAG ; 
 int NFC_DATA_SWAP_METHOD ; 
 int NFC_DATA_TRANS ; 
 int NFC_PAGE_OP ; 
 scalar_t__ NFC_REG_CMD ; 
 scalar_t__ NFC_REG_RCMD_SET ; 
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ ) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 int /*<<< orphan*/  nand_prog_page_begin_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nand_prog_page_end_op (struct nand_chip*) ; 
 int /*<<< orphan*/  sunxi_nfc_dma_op_cleanup (struct mtd_info*,int /*<<< orphan*/ ,struct scatterlist*) ; 
 int sunxi_nfc_dma_op_prepare (struct mtd_info*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct scatterlist*) ; 
 int /*<<< orphan*/  sunxi_nfc_hw_ecc_disable (struct mtd_info*) ; 
 int /*<<< orphan*/  sunxi_nfc_hw_ecc_enable (struct mtd_info*) ; 
 int /*<<< orphan*/  sunxi_nfc_hw_ecc_set_prot_oob_bytes (struct mtd_info*,int /*<<< orphan*/  const*,int,int,int) ; 
 int /*<<< orphan*/  sunxi_nfc_hw_ecc_write_extra_oob (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int sunxi_nfc_hw_ecc_write_page (struct mtd_info*,struct nand_chip*,int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  sunxi_nfc_randomizer_config (struct mtd_info*,int,int) ; 
 int /*<<< orphan*/  sunxi_nfc_randomizer_disable (struct mtd_info*) ; 
 int /*<<< orphan*/  sunxi_nfc_randomizer_enable (struct mtd_info*) ; 
 int sunxi_nfc_wait_cmd_fifo_empty (struct sunxi_nfc*) ; 
 int sunxi_nfc_wait_events (struct sunxi_nfc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct sunxi_nfc* to_sunxi_nfc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int sunxi_nfc_hw_ecc_write_page_dma(struct mtd_info *mtd,
					   struct nand_chip *chip,
					   const u8 *buf,
					   int oob_required,
					   int page)
{
	struct nand_chip *nand = mtd_to_nand(mtd);
	struct sunxi_nfc *nfc = to_sunxi_nfc(nand->controller);
	struct nand_ecc_ctrl *ecc = &nand->ecc;
	struct scatterlist sg;
	int ret, i;

	ret = sunxi_nfc_wait_cmd_fifo_empty(nfc);
	if (ret)
		return ret;

	ret = sunxi_nfc_dma_op_prepare(mtd, buf, ecc->size, ecc->steps,
				       DMA_TO_DEVICE, &sg);
	if (ret)
		goto pio_fallback;

	for (i = 0; i < ecc->steps; i++) {
		const u8 *oob = nand->oob_poi + (i * (ecc->bytes + 4));

		sunxi_nfc_hw_ecc_set_prot_oob_bytes(mtd, oob, i, !i, page);
	}

	nand_prog_page_begin_op(chip, page, 0, NULL, 0);

	sunxi_nfc_hw_ecc_enable(mtd);
	sunxi_nfc_randomizer_config(mtd, page, false);
	sunxi_nfc_randomizer_enable(mtd);

	writel((NAND_CMD_RNDIN << 8) | NAND_CMD_PAGEPROG,
	       nfc->regs + NFC_REG_RCMD_SET);

	dma_async_issue_pending(nfc->dmac);

	writel(NFC_PAGE_OP | NFC_DATA_SWAP_METHOD |
	       NFC_DATA_TRANS | NFC_ACCESS_DIR,
	       nfc->regs + NFC_REG_CMD);

	ret = sunxi_nfc_wait_events(nfc, NFC_CMD_INT_FLAG, false, 0);
	if (ret)
		dmaengine_terminate_all(nfc->dmac);

	sunxi_nfc_randomizer_disable(mtd);
	sunxi_nfc_hw_ecc_disable(mtd);

	sunxi_nfc_dma_op_cleanup(mtd, DMA_TO_DEVICE, &sg);

	if (ret)
		return ret;

	if (oob_required || (chip->options & NAND_NEED_SCRAMBLING))
		/* TODO: use DMA to transfer extra OOB bytes ? */
		sunxi_nfc_hw_ecc_write_extra_oob(mtd, chip->oob_poi,
						 NULL, page);

	return nand_prog_page_end_op(chip);

pio_fallback:
	return sunxi_nfc_hw_ecc_write_page(mtd, chip, buf, oob_required, page);
}