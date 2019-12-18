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
struct TYPE_2__ {int /*<<< orphan*/  (* select_chip ) (struct nand_chip*,int) ;} ;
struct nand_chip {int cur_cs; TYPE_1__ legacy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct nand_chip*,int) ; 

void nand_deselect_target(struct nand_chip *chip)
{
	if (chip->legacy.select_chip)
		chip->legacy.select_chip(chip, -1);

	chip->cur_cs = -1;
}