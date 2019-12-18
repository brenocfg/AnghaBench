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
struct nand_chip {int dummy; } ;
struct ingenic_nfc {size_t selected; TYPE_2__* soc_info; int /*<<< orphan*/  dev; struct ingenic_nand_cs* cs; } ;
struct ingenic_nand_cs {scalar_t__ base; int /*<<< orphan*/  bank; } ;
struct TYPE_3__ {int /*<<< orphan*/  controller; } ;
struct ingenic_nand {TYPE_1__ chip; } ;
struct TYPE_4__ {scalar_t__ cmd_offset; scalar_t__ addr_offset; } ;

/* Variables and functions */
 unsigned int NAND_ALE ; 
 unsigned int NAND_CLE ; 
 int NAND_CMD_NONE ; 
 unsigned int NAND_NCE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  jz4780_nemc_assert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  nand_to_mtd (struct nand_chip*) ; 
 struct ingenic_nand* to_ingenic_nand (int /*<<< orphan*/ ) ; 
 struct ingenic_nfc* to_ingenic_nfc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static void ingenic_nand_cmd_ctrl(struct nand_chip *chip, int cmd,
				  unsigned int ctrl)
{
	struct ingenic_nand *nand = to_ingenic_nand(nand_to_mtd(chip));
	struct ingenic_nfc *nfc = to_ingenic_nfc(nand->chip.controller);
	struct ingenic_nand_cs *cs;

	if (WARN_ON(nfc->selected < 0))
		return;

	cs = &nfc->cs[nfc->selected];

	jz4780_nemc_assert(nfc->dev, cs->bank, ctrl & NAND_NCE);

	if (cmd == NAND_CMD_NONE)
		return;

	if (ctrl & NAND_ALE)
		writeb(cmd, cs->base + nfc->soc_info->addr_offset);
	else if (ctrl & NAND_CLE)
		writeb(cmd, cs->base + nfc->soc_info->cmd_offset);
}