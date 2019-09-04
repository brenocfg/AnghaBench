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
struct TYPE_2__ {int /*<<< orphan*/  IO_ADDR_W; int /*<<< orphan*/  IO_ADDR_R; } ;
struct davinci_nand_info {TYPE_1__ chip; int /*<<< orphan*/  current_cs; scalar_t__ mask_chipsel; int /*<<< orphan*/  vaddr; } ;

/* Variables and functions */
 struct davinci_nand_info* to_davinci_nand (struct mtd_info*) ; 

__attribute__((used)) static void nand_davinci_select_chip(struct mtd_info *mtd, int chip)
{
	struct davinci_nand_info	*info = to_davinci_nand(mtd);

	info->current_cs = info->vaddr;

	/* maybe kick in a second chipselect */
	if (chip > 0)
		info->current_cs += info->mask_chipsel;

	info->chip.IO_ADDR_W = info->current_cs;
	info->chip.IO_ADDR_R = info->chip.IO_ADDR_W;
}