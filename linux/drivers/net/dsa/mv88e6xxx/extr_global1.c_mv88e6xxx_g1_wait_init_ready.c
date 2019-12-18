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
 int /*<<< orphan*/  MV88E6XXX_G1_STS ; 
 int /*<<< orphan*/  MV88E6XXX_G1_STS_INIT_READY ; 
 int __bf_shf (int /*<<< orphan*/ ) ; 
 int mv88e6xxx_g1_wait_bit (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int mv88e6xxx_g1_wait_init_ready(struct mv88e6xxx_chip *chip)
{
	int bit = __bf_shf(MV88E6XXX_G1_STS_INIT_READY);

	/* Wait up to 1 second for the switch to be ready. The InitReady bit 11
	 * is set to a one when all units inside the device (ATU, VTU, etc.)
	 * have finished their initialization and are ready to accept frames.
	 */
	return mv88e6xxx_g1_wait_bit(chip, MV88E6XXX_G1_STS, bit, 1);
}