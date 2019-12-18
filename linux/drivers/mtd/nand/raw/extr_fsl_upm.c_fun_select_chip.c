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
struct TYPE_2__ {scalar_t__ IO_ADDR_R; scalar_t__ IO_ADDR_W; int /*<<< orphan*/  (* cmd_ctrl ) (struct nand_chip*,int /*<<< orphan*/ ,int) ;} ;
struct nand_chip {TYPE_1__ legacy; } ;
struct fsl_upm_nand {int mchip_number; scalar_t__* mchip_offsets; scalar_t__ io_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  NAND_CMD_NONE ; 
 int NAND_CTRL_CHANGE ; 
 int NAND_MAX_CHIPS ; 
 int /*<<< orphan*/  nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  stub1 (struct nand_chip*,int /*<<< orphan*/ ,int) ; 
 struct fsl_upm_nand* to_fsl_upm_nand (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fun_select_chip(struct nand_chip *chip, int mchip_nr)
{
	struct fsl_upm_nand *fun = to_fsl_upm_nand(nand_to_mtd(chip));

	if (mchip_nr == -1) {
		chip->legacy.cmd_ctrl(chip, NAND_CMD_NONE, 0 | NAND_CTRL_CHANGE);
	} else if (mchip_nr >= 0 && mchip_nr < NAND_MAX_CHIPS) {
		fun->mchip_number = mchip_nr;
		chip->legacy.IO_ADDR_R = fun->io_base + fun->mchip_offsets[mchip_nr];
		chip->legacy.IO_ADDR_W = chip->legacy.IO_ADDR_R;
	} else {
		BUG();
	}
}