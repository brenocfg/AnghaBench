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
struct mtd_info {int dummy; } ;
struct jz4780_nand_cs {int /*<<< orphan*/  bank; } ;
struct jz4780_nand_controller {size_t selected; int /*<<< orphan*/  dev; struct jz4780_nand_cs* cs; } ;
struct TYPE_2__ {int /*<<< orphan*/  controller; } ;
struct jz4780_nand_chip {TYPE_1__ chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  jz4780_nemc_assert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct jz4780_nand_chip* to_jz4780_nand_chip (struct mtd_info*) ; 
 struct jz4780_nand_controller* to_jz4780_nand_controller (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jz4780_nand_select_chip(struct mtd_info *mtd, int chipnr)
{
	struct jz4780_nand_chip *nand = to_jz4780_nand_chip(mtd);
	struct jz4780_nand_controller *nfc = to_jz4780_nand_controller(nand->chip.controller);
	struct jz4780_nand_cs *cs;

	/* Ensure the currently selected chip is deasserted. */
	if (chipnr == -1 && nfc->selected >= 0) {
		cs = &nfc->cs[nfc->selected];
		jz4780_nemc_assert(nfc->dev, cs->bank, false);
	}

	nfc->selected = chipnr;
}