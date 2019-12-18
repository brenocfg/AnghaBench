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
struct phy_device {int interrupts; TYPE_1__* drv; } ;
struct TYPE_2__ {int (* config_intr ) (struct phy_device*) ;} ;

/* Variables and functions */
 int stub1 (struct phy_device*) ; 

__attribute__((used)) static int phy_config_interrupt(struct phy_device *phydev, bool interrupts)
{
	phydev->interrupts = interrupts ? 1 : 0;
	if (phydev->drv->config_intr)
		return phydev->drv->config_intr(phydev);

	return 0;
}