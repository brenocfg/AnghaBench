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
typedef  scalar_t__ u8 ;
struct phy_device {int dummy; } ;

/* Variables and functions */
 int phy_loopback (struct phy_device*,int) ; 
 int phy_resume (struct phy_device*) ; 
 int phy_suspend (struct phy_device*) ; 

__attribute__((used)) static int hns_nic_config_phy_loopback(struct phy_device *phy_dev, u8 en)
{
	int err;

	if (en) {
		/* Doing phy loopback in offline state, phy resuming is
		 * needed to power up the device.
		 */
		err = phy_resume(phy_dev);
		if (err)
			goto out;

		err = phy_loopback(phy_dev, true);
	} else {
		err = phy_loopback(phy_dev, false);
		if (err)
			goto out;

		err = phy_suspend(phy_dev);
	}

out:
	return err;
}