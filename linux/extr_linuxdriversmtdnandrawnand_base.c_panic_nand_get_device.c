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
struct nand_chip {int state; TYPE_1__* controller; } ;
struct mtd_info {int dummy; } ;
struct TYPE_2__ {struct nand_chip* active; } ;

/* Variables and functions */

__attribute__((used)) static void panic_nand_get_device(struct nand_chip *chip,
		      struct mtd_info *mtd, int new_state)
{
	/* Hardware controller shared among independent devices */
	chip->controller->active = chip;
	chip->state = new_state;
}