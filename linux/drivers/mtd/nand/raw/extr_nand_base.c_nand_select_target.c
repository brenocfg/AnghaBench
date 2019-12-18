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
struct TYPE_2__ {int /*<<< orphan*/  (* select_chip ) (struct nand_chip*,unsigned int) ;} ;
struct nand_chip {unsigned int cur_cs; TYPE_1__ legacy; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 unsigned int nanddev_ntargets (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nand_chip*,unsigned int) ; 

void nand_select_target(struct nand_chip *chip, unsigned int cs)
{
	/*
	 * cs should always lie between 0 and nanddev_ntargets(), when that's
	 * not the case it's a bug and the caller should be fixed.
	 */
	if (WARN_ON(cs > nanddev_ntargets(&chip->base)))
		return;

	chip->cur_cs = cs;

	if (chip->legacy.select_chip)
		chip->legacy.select_chip(chip, cs);
}