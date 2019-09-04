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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct sunxi_nfc {scalar_t__ regs; int /*<<< orphan*/  dmac; } ;
struct scatterlist {int dummy; } ;
struct nand_ecc_ctrl {int size; int bytes; int /*<<< orphan*/  strength; } ;
struct nand_chip {int options; int /*<<< orphan*/ * oob_poi; struct nand_ecc_ctrl ecc; int /*<<< orphan*/  controller; } ;
struct mtd_info {int writesize; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int NAND_CMD_READSTART ; 
 int NAND_CMD_RNDOUT ; 
 int NAND_CMD_RNDOUTSTART ; 
 int NAND_NEED_SCRAMBLING ; 
 int /*<<< orphan*/  NFC_CMD_INT_FLAG ; 
 int NFC_DATA_SWAP_METHOD ; 
 int NFC_DATA_TRANS ; 
 int NFC_ECC_ERR (int) ; 
 int NFC_ECC_ERR_MSK ; 
 int NFC_PAGE_OP ; 
 scalar_t__ NFC_REG_CMD ; 
 scalar_t__ NFC_REG_ECC_ST ; 
 scalar_t__ NFC_REG_RCMD_SET ; 
 int /*<<< orphan*/  dma_async_issue_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ ) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 int /*<<< orphan*/  nand_change_read_column_op (struct nand_chip*,int,int /*<<< orphan*/ *,int,int) ; 
 int nand_check_erased_ecc_chunk (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  sunxi_nfc_dma_op_cleanup (struct mtd_info*,int /*<<< orphan*/ ,struct scatterlist*) ; 
 int sunxi_nfc_dma_op_prepare (struct mtd_info*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,struct scatterlist*) ; 
 int sunxi_nfc_hw_ecc_correct (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int*) ; 
 int /*<<< orphan*/  sunxi_nfc_hw_ecc_disable (struct mtd_info*) ; 
 int /*<<< orphan*/  sunxi_nfc_hw_ecc_enable (struct mtd_info*) ; 
 int /*<<< orphan*/  sunxi_nfc_hw_ecc_get_prot_oob_bytes (struct mtd_info*,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  sunxi_nfc_hw_ecc_read_extra_oob (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  sunxi_nfc_hw_ecc_update_stats (struct mtd_info*,unsigned int*,int) ; 
 int /*<<< orphan*/  sunxi_nfc_randomizer_config (struct mtd_info*,int,int) ; 
 int /*<<< orphan*/  sunxi_nfc_randomizer_disable (struct mtd_info*) ; 
 int /*<<< orphan*/  sunxi_nfc_randomizer_enable (struct mtd_info*) ; 
 int sunxi_nfc_wait_cmd_fifo_empty (struct sunxi_nfc*) ; 
 int sunxi_nfc_wait_events (struct sunxi_nfc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct sunxi_nfc* to_sunxi_nfc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int sunxi_nfc_hw_ecc_read_chunks_dma(struct mtd_info *mtd, uint8_t *buf,
					    int oob_required, int page,
					    int nchunks)
{
	struct nand_chip *nand = mtd_to_nand(mtd);
	bool randomized = nand->options & NAND_NEED_SCRAMBLING;
	struct sunxi_nfc *nfc = to_sunxi_nfc(nand->controller);
	struct nand_ecc_ctrl *ecc = &nand->ecc;
	unsigned int max_bitflips = 0;
	int ret, i, raw_mode = 0;
	struct scatterlist sg;
	u32 status;

	ret = sunxi_nfc_wait_cmd_fifo_empty(nfc);
	if (ret)
		return ret;

	ret = sunxi_nfc_dma_op_prepare(mtd, buf, ecc->size, nchunks,
				       DMA_FROM_DEVICE, &sg);
	if (ret)
		return ret;

	sunxi_nfc_hw_ecc_enable(mtd);
	sunxi_nfc_randomizer_config(mtd, page, false);
	sunxi_nfc_randomizer_enable(mtd);

	writel((NAND_CMD_RNDOUTSTART << 16) | (NAND_CMD_RNDOUT << 8) |
	       NAND_CMD_READSTART, nfc->regs + NFC_REG_RCMD_SET);

	dma_async_issue_pending(nfc->dmac);

	writel(NFC_PAGE_OP | NFC_DATA_SWAP_METHOD | NFC_DATA_TRANS,
	       nfc->regs + NFC_REG_CMD);

	ret = sunxi_nfc_wait_events(nfc, NFC_CMD_INT_FLAG, false, 0);
	if (ret)
		dmaengine_terminate_all(nfc->dmac);

	sunxi_nfc_randomizer_disable(mtd);
	sunxi_nfc_hw_ecc_disable(mtd);

	sunxi_nfc_dma_op_cleanup(mtd, DMA_FROM_DEVICE, &sg);

	if (ret)
		return ret;

	status = readl(nfc->regs + NFC_REG_ECC_ST);

	for (i = 0; i < nchunks; i++) {
		int data_off = i * ecc->size;
		int oob_off = i * (ecc->bytes + 4);
		u8 *data = buf + data_off;
		u8 *oob = nand->oob_poi + oob_off;
		bool erased;

		ret = sunxi_nfc_hw_ecc_correct(mtd, randomized ? data : NULL,
					       oob_required ? oob : NULL,
					       i, status, &erased);

		/* ECC errors are handled in the second loop. */
		if (ret < 0)
			continue;

		if (oob_required && !erased) {
			/* TODO: use DMA to retrieve OOB */
			nand_change_read_column_op(nand,
						   mtd->writesize + oob_off,
						   oob, ecc->bytes + 4, false);

			sunxi_nfc_hw_ecc_get_prot_oob_bytes(mtd, oob, i,
							    !i, page);
		}

		if (erased)
			raw_mode = 1;

		sunxi_nfc_hw_ecc_update_stats(mtd, &max_bitflips, ret);
	}

	if (status & NFC_ECC_ERR_MSK) {
		for (i = 0; i < nchunks; i++) {
			int data_off = i * ecc->size;
			int oob_off = i * (ecc->bytes + 4);
			u8 *data = buf + data_off;
			u8 *oob = nand->oob_poi + oob_off;

			if (!(status & NFC_ECC_ERR(i)))
				continue;

			/*
			 * Re-read the data with the randomizer disabled to
			 * identify bitflips in erased pages.
			 * TODO: use DMA to read page in raw mode
			 */
			if (randomized)
				nand_change_read_column_op(nand, data_off,
							   data, ecc->size,
							   false);

			/* TODO: use DMA to retrieve OOB */
			nand_change_read_column_op(nand,
						   mtd->writesize + oob_off,
						   oob, ecc->bytes + 4, false);

			ret = nand_check_erased_ecc_chunk(data,	ecc->size,
							  oob, ecc->bytes + 4,
							  NULL, 0,
							  ecc->strength);
			if (ret >= 0)
				raw_mode = 1;

			sunxi_nfc_hw_ecc_update_stats(mtd, &max_bitflips, ret);
		}
	}

	if (oob_required)
		sunxi_nfc_hw_ecc_read_extra_oob(mtd, nand->oob_poi,
						NULL, !raw_mode,
						page);

	return max_bitflips;
}