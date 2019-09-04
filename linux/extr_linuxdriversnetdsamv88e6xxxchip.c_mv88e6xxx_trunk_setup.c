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
struct mv88e6xxx_chip {TYPE_1__* info; } ;
struct TYPE_2__ {scalar_t__ global2_addr; } ;

/* Variables and functions */
 int mv88e6xxx_g2_trunk_clear (struct mv88e6xxx_chip*) ; 

__attribute__((used)) static int mv88e6xxx_trunk_setup(struct mv88e6xxx_chip *chip)
{
	/* Clear all trunk masks and mapping */
	if (chip->info->global2_addr)
		return mv88e6xxx_g2_trunk_clear(chip);

	return 0;
}