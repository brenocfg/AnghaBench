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
struct mv88e6xxx_chip {TYPE_2__* info; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {scalar_t__ ppu_disable; scalar_t__ ppu_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  mv88e6xxx_phy_ppu_state_destroy (struct mv88e6xxx_chip*) ; 

void mv88e6xxx_phy_destroy(struct mv88e6xxx_chip *chip)
{
	if (chip->info->ops->ppu_enable && chip->info->ops->ppu_disable)
		mv88e6xxx_phy_ppu_state_destroy(chip);
}