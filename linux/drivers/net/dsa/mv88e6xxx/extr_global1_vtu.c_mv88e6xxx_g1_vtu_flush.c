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
 int /*<<< orphan*/  MV88E6XXX_G1_VTU_OP_FLUSH_ALL ; 
 int mv88e6xxx_g1_vtu_op (struct mv88e6xxx_chip*,int /*<<< orphan*/ ) ; 
 int mv88e6xxx_g1_vtu_op_wait (struct mv88e6xxx_chip*) ; 

int mv88e6xxx_g1_vtu_flush(struct mv88e6xxx_chip *chip)
{
	int err;

	err = mv88e6xxx_g1_vtu_op_wait(chip);
	if (err)
		return err;

	return mv88e6xxx_g1_vtu_op(chip, MV88E6XXX_G1_VTU_OP_FLUSH_ALL);
}