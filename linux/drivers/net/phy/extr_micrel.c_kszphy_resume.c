#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct phy_device {TYPE_1__* drv; int /*<<< orphan*/  interrupts; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* config_intr ) (struct phy_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_INTERRUPT_ENABLED ; 
 int /*<<< orphan*/  genphy_resume (struct phy_device*) ; 
 int kszphy_config_reset (struct phy_device*) ; 
 scalar_t__ phy_interrupt_is_valid (struct phy_device*) ; 
 int /*<<< orphan*/  stub1 (struct phy_device*) ; 

__attribute__((used)) static int kszphy_resume(struct phy_device *phydev)
{
	int ret;

	genphy_resume(phydev);

	ret = kszphy_config_reset(phydev);
	if (ret)
		return ret;

	/* Enable PHY Interrupts */
	if (phy_interrupt_is_valid(phydev)) {
		phydev->interrupts = PHY_INTERRUPT_ENABLED;
		if (phydev->drv->config_intr)
			phydev->drv->config_intr(phydev);
	}

	return 0;
}