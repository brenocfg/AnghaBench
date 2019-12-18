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
struct phy_device {int /*<<< orphan*/ * adjust_link; } ;

/* Variables and functions */
 int /*<<< orphan*/  phy_detach (struct phy_device*) ; 
 int /*<<< orphan*/  phy_free_interrupt (struct phy_device*) ; 
 scalar_t__ phy_interrupt_is_valid (struct phy_device*) ; 
 scalar_t__ phy_is_started (struct phy_device*) ; 
 int /*<<< orphan*/  phy_stop (struct phy_device*) ; 

void phy_disconnect(struct phy_device *phydev)
{
	if (phy_is_started(phydev))
		phy_stop(phydev);

	if (phy_interrupt_is_valid(phydev))
		phy_free_interrupt(phydev);

	phydev->adjust_link = NULL;

	phy_detach(phydev);
}