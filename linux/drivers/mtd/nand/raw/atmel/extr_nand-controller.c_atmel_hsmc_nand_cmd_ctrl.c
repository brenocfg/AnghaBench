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
struct nand_chip {int /*<<< orphan*/  controller; } ;
struct atmel_nand {TYPE_2__* activecs; } ;
struct TYPE_3__ {scalar_t__ naddrs; int* addrs; int ncmds; int* cmds; int /*<<< orphan*/  cs; } ;
struct atmel_hsmc_nand_controller {TYPE_1__ op; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ ATMEL_NFC_MAX_ADDR_CYCLES ; 
 unsigned int NAND_ALE ; 
 unsigned int NAND_CLE ; 
 int NAND_CMD_NONE ; 
 int /*<<< orphan*/  atmel_nfc_exec_op (struct atmel_hsmc_nand_controller*,int) ; 
 struct atmel_nand* to_atmel_nand (struct nand_chip*) ; 
 struct atmel_hsmc_nand_controller* to_hsmc_nand_controller (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atmel_hsmc_nand_cmd_ctrl(struct nand_chip *chip, int dat,
				     unsigned int ctrl)
{
	struct atmel_nand *nand = to_atmel_nand(chip);
	struct atmel_hsmc_nand_controller *nc;

	nc = to_hsmc_nand_controller(chip->controller);

	if (ctrl & NAND_ALE) {
		if (nc->op.naddrs == ATMEL_NFC_MAX_ADDR_CYCLES)
			return;

		nc->op.addrs[nc->op.naddrs++] = dat;
	} else if (ctrl & NAND_CLE) {
		if (nc->op.ncmds > 1)
			return;

		nc->op.cmds[nc->op.ncmds++] = dat;
	}

	if (dat == NAND_CMD_NONE) {
		nc->op.cs = nand->activecs->id;
		atmel_nfc_exec_op(nc, true);
	}
}