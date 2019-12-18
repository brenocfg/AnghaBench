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
typedef  int /*<<< orphan*/  u16 ;
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E6390_G1_MONITOR_MGMT_CTL_PTR_0180C200000XHI ; 
 int /*<<< orphan*/  MV88E6390_G1_MONITOR_MGMT_CTL_PTR_0180C200000XLO ; 
 int /*<<< orphan*/  MV88E6390_G1_MONITOR_MGMT_CTL_PTR_0180C200002XHI ; 
 int /*<<< orphan*/  MV88E6390_G1_MONITOR_MGMT_CTL_PTR_0180C200002XLO ; 
 int mv88e6390_g1_monitor_write (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int) ; 

int mv88e6390_g1_mgmt_rsvd2cpu(struct mv88e6xxx_chip *chip)
{
	u16 ptr;
	int err;

	/* 01:80:c2:00:00:00-01:80:c2:00:00:07 are Management */
	ptr = MV88E6390_G1_MONITOR_MGMT_CTL_PTR_0180C200000XLO;
	err = mv88e6390_g1_monitor_write(chip, ptr, 0xff);
	if (err)
		return err;

	/* 01:80:c2:00:00:08-01:80:c2:00:00:0f are Management */
	ptr = MV88E6390_G1_MONITOR_MGMT_CTL_PTR_0180C200000XHI;
	err = mv88e6390_g1_monitor_write(chip, ptr, 0xff);
	if (err)
		return err;

	/* 01:80:c2:00:00:20-01:80:c2:00:00:27 are Management */
	ptr = MV88E6390_G1_MONITOR_MGMT_CTL_PTR_0180C200002XLO;
	err = mv88e6390_g1_monitor_write(chip, ptr, 0xff);
	if (err)
		return err;

	/* 01:80:c2:00:00:28-01:80:c2:00:00:2f are Management */
	ptr = MV88E6390_G1_MONITOR_MGMT_CTL_PTR_0180C200002XHI;
	err = mv88e6390_g1_monitor_write(chip, ptr, 0xff);
	if (err)
		return err;

	return 0;
}