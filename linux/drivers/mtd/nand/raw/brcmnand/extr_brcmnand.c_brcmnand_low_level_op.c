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
typedef  int u32 ;
struct nand_chip {int dummy; } ;
struct brcmnand_host {struct brcmnand_controller* ctrl; struct nand_chip chip; } ;
struct brcmnand_controller {int /*<<< orphan*/  dev; } ;
typedef  enum brcmnand_llop_type { ____Placeholder_brcmnand_llop_type } brcmnand_llop_type ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMNAND_LL_OP ; 
 int /*<<< orphan*/  CMD_LOW_LEVEL_OP ; 
 int LLOP_ALE ; 
 int LLOP_CLE ; 
 int LLOP_DATA_MASK ; 
 int LLOP_RE ; 
 int LLOP_RETURN_IDLE ; 
 int LLOP_WE ; 
#define  LL_OP_ADDR 131 
#define  LL_OP_CMD 130 
#define  LL_OP_RD 129 
#define  LL_OP_WR 128 
 int /*<<< orphan*/  brcmnand_read_reg (struct brcmnand_controller*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmnand_send_cmd (struct brcmnand_host*,int /*<<< orphan*/ ) ; 
 int brcmnand_waitfunc (struct nand_chip*) ; 
 int /*<<< orphan*/  brcmnand_write_reg (struct brcmnand_controller*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int brcmnand_low_level_op(struct brcmnand_host *host,
				 enum brcmnand_llop_type type, u32 data,
				 bool last_op)
{
	struct nand_chip *chip = &host->chip;
	struct brcmnand_controller *ctrl = host->ctrl;
	u32 tmp;

	tmp = data & LLOP_DATA_MASK;
	switch (type) {
	case LL_OP_CMD:
		tmp |= LLOP_WE | LLOP_CLE;
		break;
	case LL_OP_ADDR:
		/* WE | ALE */
		tmp |= LLOP_WE | LLOP_ALE;
		break;
	case LL_OP_WR:
		/* WE */
		tmp |= LLOP_WE;
		break;
	case LL_OP_RD:
		/* RE */
		tmp |= LLOP_RE;
		break;
	}
	if (last_op)
		/* RETURN_IDLE */
		tmp |= LLOP_RETURN_IDLE;

	dev_dbg(ctrl->dev, "ll_op cmd %#x\n", tmp);

	brcmnand_write_reg(ctrl, BRCMNAND_LL_OP, tmp);
	(void)brcmnand_read_reg(ctrl, BRCMNAND_LL_OP);

	brcmnand_send_cmd(host, CMD_LOW_LEVEL_OP);
	return brcmnand_waitfunc(chip);
}