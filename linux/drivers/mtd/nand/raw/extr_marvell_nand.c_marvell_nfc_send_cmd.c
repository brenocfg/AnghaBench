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
typedef  int /*<<< orphan*/  u32 ;
struct nand_chip {int /*<<< orphan*/  controller; } ;
struct marvell_nfc_op {int* ndcb; } ;
struct marvell_nfc {scalar_t__ regs; TYPE_1__* caps; int /*<<< orphan*/  dev; } ;
struct marvell_nand_chip {int dummy; } ;
struct TYPE_4__ {int ndcb0_csel; } ;
struct TYPE_3__ {int /*<<< orphan*/  is_nfcv2; } ;

/* Variables and functions */
 scalar_t__ NDCB0 ; 
 int NDCB0_ADDR_GET_NUM_CYC (int) ; 
 int NDCB0_LEN_OVRD ; 
 scalar_t__ NDCR ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int,int) ; 
 scalar_t__ readl_relaxed (scalar_t__) ; 
 struct marvell_nand_chip* to_marvell_nand (struct nand_chip*) ; 
 struct marvell_nfc* to_marvell_nfc (int /*<<< orphan*/ ) ; 
 TYPE_2__* to_nand_sel (struct marvell_nand_chip*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void marvell_nfc_send_cmd(struct nand_chip *chip,
				 struct marvell_nfc_op *nfc_op)
{
	struct marvell_nand_chip *marvell_nand = to_marvell_nand(chip);
	struct marvell_nfc *nfc = to_marvell_nfc(chip->controller);

	dev_dbg(nfc->dev, "\nNDCR:  0x%08x\n"
		"NDCB0: 0x%08x\nNDCB1: 0x%08x\nNDCB2: 0x%08x\nNDCB3: 0x%08x\n",
		(u32)readl_relaxed(nfc->regs + NDCR), nfc_op->ndcb[0],
		nfc_op->ndcb[1], nfc_op->ndcb[2], nfc_op->ndcb[3]);

	writel_relaxed(to_nand_sel(marvell_nand)->ndcb0_csel | nfc_op->ndcb[0],
		       nfc->regs + NDCB0);
	writel_relaxed(nfc_op->ndcb[1], nfc->regs + NDCB0);
	writel(nfc_op->ndcb[2], nfc->regs + NDCB0);

	/*
	 * Write NDCB0 four times only if LEN_OVRD is set or if ADDR6 or ADDR7
	 * fields are used (only available on NFCv2).
	 */
	if (nfc_op->ndcb[0] & NDCB0_LEN_OVRD ||
	    NDCB0_ADDR_GET_NUM_CYC(nfc_op->ndcb[0]) >= 6) {
		if (!WARN_ON_ONCE(!nfc->caps->is_nfcv2))
			writel(nfc_op->ndcb[3], nfc->regs + NDCB0);
	}
}