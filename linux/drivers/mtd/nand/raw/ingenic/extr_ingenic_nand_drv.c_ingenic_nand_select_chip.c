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
struct nand_chip {int dummy; } ;
struct ingenic_nfc {size_t selected; int /*<<< orphan*/  dev; struct ingenic_nand_cs* cs; } ;
struct ingenic_nand_cs {int /*<<< orphan*/  bank; } ;
struct TYPE_2__ {int /*<<< orphan*/  controller; } ;
struct ingenic_nand {TYPE_1__ chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  jz4780_nemc_assert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nand_to_mtd (struct nand_chip*) ; 
 struct ingenic_nand* to_ingenic_nand (int /*<<< orphan*/ ) ; 
 struct ingenic_nfc* to_ingenic_nfc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ingenic_nand_select_chip(struct nand_chip *chip, int chipnr)
{
	struct ingenic_nand *nand = to_ingenic_nand(nand_to_mtd(chip));
	struct ingenic_nfc *nfc = to_ingenic_nfc(nand->chip.controller);
	struct ingenic_nand_cs *cs;

	/* Ensure the currently selected chip is deasserted. */
	if (chipnr == -1 && nfc->selected >= 0) {
		cs = &nfc->cs[nfc->selected];
		jz4780_nemc_assert(nfc->dev, cs->bank, false);
	}

	nfc->selected = chipnr;
}