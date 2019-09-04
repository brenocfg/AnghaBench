#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nand_subop {TYPE_1__* instrs; } ;
struct nand_chip {int /*<<< orphan*/  controller; } ;
struct marvell_nfc_op {int* ndcb; int /*<<< orphan*/  cle_ale_delay_ns; int /*<<< orphan*/  data_instr; } ;
struct marvell_nfc {scalar_t__ regs; } ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
#define  NAND_OP_ADDR_INSTR 131 
#define  NAND_OP_CMD_INSTR 130 
#define  NAND_OP_DATA_IN_INSTR 129 
#define  NAND_OP_DATA_OUT_INSTR 128 
 int NDCB0_CMD_TYPE (int /*<<< orphan*/ ) ; 
 int NDCB0_CMD_XTYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ NDCR ; 
 int NDCR_ND_RUN ; 
 int NDSR_RDDREQ ; 
 int NDSR_WRDREQ ; 
 int /*<<< orphan*/  TYPE_MASK ; 
 int /*<<< orphan*/  TYPE_NAKED_ADDR ; 
 int /*<<< orphan*/  TYPE_NAKED_CMD ; 
 int /*<<< orphan*/  TYPE_READ ; 
 int /*<<< orphan*/  TYPE_WRITE ; 
 int /*<<< orphan*/  XTYPE_LAST_NAKED_RW ; 
 int /*<<< orphan*/  XTYPE_MASK ; 
 int /*<<< orphan*/  cond_delay (int /*<<< orphan*/ ) ; 
 int marvell_nfc_end_cmd (struct nand_chip*,int,char*) ; 
 int /*<<< orphan*/  marvell_nfc_parse_instructions (struct nand_chip*,struct nand_subop const*,struct marvell_nfc_op*) ; 
 int marvell_nfc_prepare_cmd (struct nand_chip*) ; 
 int /*<<< orphan*/  marvell_nfc_send_cmd (struct nand_chip*,struct marvell_nfc_op*) ; 
 int marvell_nfc_wait_cmdd (struct nand_chip*) ; 
 int /*<<< orphan*/  marvell_nfc_xfer_data_pio (struct nand_chip*,struct nand_subop const*,struct marvell_nfc_op*) ; 
 int readl (scalar_t__) ; 
 struct marvell_nfc* to_marvell_nfc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int marvell_nfc_naked_access_exec(struct nand_chip *chip,
					 const struct nand_subop *subop)
{
	struct marvell_nfc_op nfc_op;
	int ret;

	marvell_nfc_parse_instructions(chip, subop, &nfc_op);

	/*
	 * Naked access are different in that they need to be flagged as naked
	 * by the controller. Reset the controller registers fields that inform
	 * on the type and refill them according to the ongoing operation.
	 */
	nfc_op.ndcb[0] &= ~(NDCB0_CMD_TYPE(TYPE_MASK) |
			    NDCB0_CMD_XTYPE(XTYPE_MASK));
	switch (subop->instrs[0].type) {
	case NAND_OP_CMD_INSTR:
		nfc_op.ndcb[0] |= NDCB0_CMD_TYPE(TYPE_NAKED_CMD);
		break;
	case NAND_OP_ADDR_INSTR:
		nfc_op.ndcb[0] |= NDCB0_CMD_TYPE(TYPE_NAKED_ADDR);
		break;
	case NAND_OP_DATA_IN_INSTR:
		nfc_op.ndcb[0] |= NDCB0_CMD_TYPE(TYPE_READ) |
				  NDCB0_CMD_XTYPE(XTYPE_LAST_NAKED_RW);
		break;
	case NAND_OP_DATA_OUT_INSTR:
		nfc_op.ndcb[0] |= NDCB0_CMD_TYPE(TYPE_WRITE) |
				  NDCB0_CMD_XTYPE(XTYPE_LAST_NAKED_RW);
		break;
	default:
		/* This should never happen */
		break;
	}

	ret = marvell_nfc_prepare_cmd(chip);
	if (ret)
		return ret;

	marvell_nfc_send_cmd(chip, &nfc_op);

	if (!nfc_op.data_instr) {
		ret = marvell_nfc_wait_cmdd(chip);
		cond_delay(nfc_op.cle_ale_delay_ns);
		return ret;
	}

	ret = marvell_nfc_end_cmd(chip, NDSR_RDDREQ | NDSR_WRDREQ,
				  "RDDREQ/WRDREQ while draining raw data");
	if (ret)
		return ret;

	marvell_nfc_xfer_data_pio(chip, subop, &nfc_op);
	ret = marvell_nfc_wait_cmdd(chip);
	if (ret)
		return ret;

	/*
	 * NDCR ND_RUN bit should be cleared automatically at the end of each
	 * operation but experience shows that the behavior is buggy when it
	 * comes to writes (with LEN_OVRD). Clear it by hand in this case.
	 */
	if (subop->instrs[0].type == NAND_OP_DATA_OUT_INSTR) {
		struct marvell_nfc *nfc = to_marvell_nfc(chip->controller);

		writel_relaxed(readl(nfc->regs + NDCR) & ~NDCR_ND_RUN,
			       nfc->regs + NDCR);
	}

	return 0;
}