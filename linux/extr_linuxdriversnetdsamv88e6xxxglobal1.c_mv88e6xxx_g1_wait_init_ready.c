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
typedef  int u16 ;
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int HZ ; 
 int /*<<< orphan*/  MV88E6XXX_G1_STS ; 
 int MV88E6XXX_G1_STS_INIT_READY ; 
 int jiffies ; 
 int mv88e6xxx_g1_read (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ time_after (int,unsigned long const) ; 
 scalar_t__ time_before (int,unsigned long const) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int mv88e6xxx_g1_wait_init_ready(struct mv88e6xxx_chip *chip)
{
	const unsigned long timeout = jiffies + 1 * HZ;
	u16 val;
	int err;

	/* Wait up to 1 second for the switch to be ready. The InitReady bit 11
	 * is set to a one when all units inside the device (ATU, VTU, etc.)
	 * have finished their initialization and are ready to accept frames.
	 */
	while (time_before(jiffies, timeout)) {
		err = mv88e6xxx_g1_read(chip, MV88E6XXX_G1_STS, &val);
		if (err)
			return err;

		if (val & MV88E6XXX_G1_STS_INIT_READY)
			break;

		usleep_range(1000, 2000);
	}

	if (time_after(jiffies, timeout))
		return -ETIMEDOUT;

	return 0;
}