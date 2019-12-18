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
typedef  int /*<<< orphan*/  u16 ;
struct mv88e6xxx_chip {TYPE_1__* info; } ;
struct TYPE_2__ {int /*<<< orphan*/  global1_addr; } ;

/* Variables and functions */
 int mv88e6xxx_wait_mask (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mv88e6xxx_g1_wait_mask(struct mv88e6xxx_chip *chip, int reg,
			   u16 mask, u16 val)
{
	return mv88e6xxx_wait_mask(chip, chip->info->global1_addr, reg,
				   mask, val);
}