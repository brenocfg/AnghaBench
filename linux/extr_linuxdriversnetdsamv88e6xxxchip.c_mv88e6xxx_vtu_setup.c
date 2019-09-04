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
struct TYPE_2__ {int /*<<< orphan*/  max_vid; } ;

/* Variables and functions */
 int mv88e6xxx_g1_vtu_flush (struct mv88e6xxx_chip*) ; 

__attribute__((used)) static int mv88e6xxx_vtu_setup(struct mv88e6xxx_chip *chip)
{
	if (!chip->info->max_vid)
		return 0;

	return mv88e6xxx_g1_vtu_flush(chip);
}