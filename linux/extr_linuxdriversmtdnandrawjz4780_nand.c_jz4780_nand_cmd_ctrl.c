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
struct jz4780_nand_cs {scalar_t__ base; int /*<<< orphan*/  bank; } ;
struct jz4780_nand_controller {size_t selected; int /*<<< orphan*/  dev; struct jz4780_nand_cs* cs; } ;
struct TYPE_2__ {int /*<<< orphan*/  controller; } ;
struct jz4780_nand_chip {TYPE_1__ chip; } ;

/* Variables and functions */
 unsigned int NAND_ALE ; 
 unsigned int NAND_CLE ; 
 int NAND_CMD_NONE ; 
 unsigned int NAND_NCE ; 
 scalar_t__ OFFSET_ADDR ; 
 scalar_t__ OFFSET_CMD ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  jz4780_nemc_assert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct jz4780_nand_chip* to_jz4780_nand_chip (struct mtd_info*) ; 
 struct jz4780_nand_controller* to_jz4780_nand_controller (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static void jz4780_nand_cmd_ctrl(struct mtd_info *mtd, int cmd,
				 unsigned int ctrl)
{
	struct jz4780_nand_chip *nand = to_jz4780_nand_chip(mtd);
	struct jz4780_nand_controller *nfc = to_jz4780_nand_controller(nand->chip.controller);
	struct jz4780_nand_cs *cs;

	if (WARN_ON(nfc->selected < 0))
		return;

	cs = &nfc->cs[nfc->selected];

	jz4780_nemc_assert(nfc->dev, cs->bank, ctrl & NAND_NCE);

	if (cmd == NAND_CMD_NONE)
		return;

	if (ctrl & NAND_ALE)
		writeb(cmd, cs->base + OFFSET_ADDR);
	else if (ctrl & NAND_CLE)
		writeb(cmd, cs->base + OFFSET_CMD);
}