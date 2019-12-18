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
 int /*<<< orphan*/  MV88E6XXX_G2_DEVICE_MAPPING ; 
 int MV88E6XXX_G2_DEVICE_MAPPING_UPDATE ; 
 int mv88e6xxx_g2_write (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int) ; 

int mv88e6xxx_g2_device_mapping_write(struct mv88e6xxx_chip *chip, int target,
				      int port)
{
	u16 val = (target << 8) | (port & 0x1f);
	/* Modern chips use 5 bits to define a device mapping port,
	 * but bit 4 is reserved on older chips, so it is safe to use.
	 */

	return mv88e6xxx_g2_write(chip, MV88E6XXX_G2_DEVICE_MAPPING,
				  MV88E6XXX_G2_DEVICE_MAPPING_UPDATE | val);
}