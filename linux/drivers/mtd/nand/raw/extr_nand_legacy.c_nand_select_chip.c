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
struct TYPE_2__ {int /*<<< orphan*/  (* cmd_ctrl ) (struct nand_chip*,int /*<<< orphan*/ ,int) ;} ;
struct nand_chip {TYPE_1__ legacy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  NAND_CMD_NONE ; 
 int NAND_CTRL_CHANGE ; 
 int /*<<< orphan*/  stub1 (struct nand_chip*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nand_select_chip(struct nand_chip *chip, int chipnr)
{
	switch (chipnr) {
	case -1:
		chip->legacy.cmd_ctrl(chip, NAND_CMD_NONE,
				      0 | NAND_CTRL_CHANGE);
		break;
	case 0:
		break;

	default:
		BUG();
	}
}