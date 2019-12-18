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
struct phy_device {int dummy; } ;

/* Variables and functions */
 int m88e6390_hwmon_probe (struct phy_device*) ; 
 int marvell_probe (struct phy_device*) ; 

__attribute__((used)) static int m88e6390_probe(struct phy_device *phydev)
{
	int err;

	err = marvell_probe(phydev);
	if (err)
		return err;

	return m88e6390_hwmon_probe(phydev);
}