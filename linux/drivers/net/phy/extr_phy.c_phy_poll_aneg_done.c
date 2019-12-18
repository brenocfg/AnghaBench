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
 int ETIMEDOUT ; 
 int /*<<< orphan*/  msleep (int) ; 
 int phy_aneg_done (struct phy_device*) ; 

__attribute__((used)) static int phy_poll_aneg_done(struct phy_device *phydev)
{
	unsigned int retries = 100;
	int ret;

	do {
		msleep(100);
		ret = phy_aneg_done(phydev);
	} while (!ret && --retries);

	if (!ret)
		return -ETIMEDOUT;

	return ret < 0 ? ret : 0;
}