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
struct sunxi_nfc {scalar_t__ regs; } ;
struct nand_ecc_ctrl {int size; int bytes; } ;
struct nand_chip {struct nand_ecc_ctrl ecc; int /*<<< orphan*/  controller; } ;

/* Variables and functions */
 int NFC_ACCESS_DIR ; 
 int /*<<< orphan*/  NFC_CMD_INT_FLAG ; 
 int NFC_DATA_SWAP_METHOD ; 
 int NFC_DATA_TRANS ; 
 int NFC_ECC_OP ; 
 scalar_t__ NFC_REG_CMD ; 
 int /*<<< orphan*/  nand_change_write_column_op (struct nand_chip*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sunxi_nfc_hw_ecc_set_prot_oob_bytes (struct nand_chip*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sunxi_nfc_randomizer_disable (struct nand_chip*) ; 
 int /*<<< orphan*/  sunxi_nfc_randomizer_enable (struct nand_chip*) ; 
 int /*<<< orphan*/  sunxi_nfc_randomizer_write_buf (struct nand_chip*,int /*<<< orphan*/  const*,int,int,int) ; 
 int sunxi_nfc_wait_cmd_fifo_empty (struct sunxi_nfc*) ; 
 int sunxi_nfc_wait_events (struct sunxi_nfc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct sunxi_nfc* to_sunxi_nfc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int sunxi_nfc_hw_ecc_write_chunk(struct nand_chip *nand,
					const u8 *data, int data_off,
					const u8 *oob, int oob_off,
					int *cur_off, bool bbm,
					int page)
{
	struct sunxi_nfc *nfc = to_sunxi_nfc(nand->controller);
	struct nand_ecc_ctrl *ecc = &nand->ecc;
	int ret;

	if (data_off != *cur_off)
		nand_change_write_column_op(nand, data_off, NULL, 0, false);

	sunxi_nfc_randomizer_write_buf(nand, data, ecc->size, false, page);

	if (data_off + ecc->size != oob_off)
		nand_change_write_column_op(nand, oob_off, NULL, 0, false);

	ret = sunxi_nfc_wait_cmd_fifo_empty(nfc);
	if (ret)
		return ret;

	sunxi_nfc_randomizer_enable(nand);
	sunxi_nfc_hw_ecc_set_prot_oob_bytes(nand, oob, 0, bbm, page);

	writel(NFC_DATA_TRANS | NFC_DATA_SWAP_METHOD |
	       NFC_ACCESS_DIR | NFC_ECC_OP,
	       nfc->regs + NFC_REG_CMD);

	ret = sunxi_nfc_wait_events(nfc, NFC_CMD_INT_FLAG, false, 0);
	sunxi_nfc_randomizer_disable(nand);
	if (ret)
		return ret;

	*cur_off = oob_off + ecc->bytes + 4;

	return 0;
}