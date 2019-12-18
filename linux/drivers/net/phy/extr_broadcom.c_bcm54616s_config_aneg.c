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
 int /*<<< orphan*/  bcm54xx_config_clock_delay (struct phy_device*) ; 
 int genphy_config_aneg (struct phy_device*) ; 

__attribute__((used)) static int bcm54616s_config_aneg(struct phy_device *phydev)
{
	int ret;

	/* Aneg firsly. */
	ret = genphy_config_aneg(phydev);

	/* Then we can set up the delay. */
	bcm54xx_config_clock_delay(phydev);

	return ret;
}