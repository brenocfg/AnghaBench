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
struct TYPE_4__ {int /*<<< orphan*/  IO_ADDR_W; int /*<<< orphan*/  IO_ADDR_R; } ;
struct TYPE_3__ {TYPE_2__ legacy; } ;
struct davinci_nand_info {TYPE_1__ chip; int /*<<< orphan*/  current_cs; scalar_t__ mask_chipsel; int /*<<< orphan*/  vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  nand_to_mtd (struct nand_chip*) ; 
 struct davinci_nand_info* to_davinci_nand (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nand_davinci_select_chip(struct nand_chip *nand, int chip)
{
	struct davinci_nand_info *info = to_davinci_nand(nand_to_mtd(nand));

	info->current_cs = info->vaddr;

	/* maybe kick in a second chipselect */
	if (chip > 0)
		info->current_cs += info->mask_chipsel;

	info->chip.legacy.IO_ADDR_W = info->current_cs;
	info->chip.legacy.IO_ADDR_R = info->chip.legacy.IO_ADDR_W;
}