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
 int mv88e6250_g1_reset (struct mv88e6xxx_chip*) ; 
 int mv88e6352_g1_wait_ppu_polling (struct mv88e6xxx_chip*) ; 

int mv88e6352_g1_reset(struct mv88e6xxx_chip *chip)
{
	int err;

	err = mv88e6250_g1_reset(chip);
	if (err)
		return err;

	return mv88e6352_g1_wait_ppu_polling(chip);
}