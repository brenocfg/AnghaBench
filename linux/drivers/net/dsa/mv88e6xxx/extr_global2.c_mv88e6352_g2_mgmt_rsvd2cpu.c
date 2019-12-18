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
 int mv88e6185_g2_mgmt_rsvd2cpu (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_g2_mgmt_enable_2x (struct mv88e6xxx_chip*,int) ; 

int mv88e6352_g2_mgmt_rsvd2cpu(struct mv88e6xxx_chip *chip)
{
	int err;

	/* Consider the frames with reserved multicast destination
	 * addresses matching 01:80:c2:00:00:2x as MGMT.
	 */
	err = mv88e6xxx_g2_mgmt_enable_2x(chip, 0xffff);
	if (err)
		return err;

	return mv88e6185_g2_mgmt_rsvd2cpu(chip);
}