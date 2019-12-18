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
struct phy_device {int /*<<< orphan*/  dev_flags; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  phy_interface_t ;

/* Variables and functions */
 int EINVAL ; 
 int phy_attach_direct (struct net_device*,struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ phy_interrupt_is_valid (struct phy_device*) ; 
 int /*<<< orphan*/  phy_prepare_link (struct phy_device*,void (*) (struct net_device*)) ; 
 int /*<<< orphan*/  phy_request_interrupt (struct phy_device*) ; 

int phy_connect_direct(struct net_device *dev, struct phy_device *phydev,
		       void (*handler)(struct net_device *),
		       phy_interface_t interface)
{
	int rc;

	if (!dev)
		return -EINVAL;

	rc = phy_attach_direct(dev, phydev, phydev->dev_flags, interface);
	if (rc)
		return rc;

	phy_prepare_link(phydev, handler);
	if (phy_interrupt_is_valid(phydev))
		phy_request_interrupt(phydev);

	return 0;
}