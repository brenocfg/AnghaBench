#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int mv88e6xxx_g1_atu_flush (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int) ; 
 int mv88e6xxx_g1_atu_set_age_time (struct mv88e6xxx_chip*,int) ; 
 int mv88e6xxx_g1_atu_set_learn2all (struct mv88e6xxx_chip*,int) ; 

__attribute__((used)) static int mv88e6xxx_atu_setup(struct mv88e6xxx_chip *chip)
{
	int err;

	err = mv88e6xxx_g1_atu_flush(chip, 0, true);
	if (err)
		return err;

	err = mv88e6xxx_g1_atu_set_learn2all(chip, true);
	if (err)
		return err;

	return mv88e6xxx_g1_atu_set_age_time(chip, 300000);
}