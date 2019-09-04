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
struct net_device {scalar_t__ phydev; } ;

/* Variables and functions */
 int /*<<< orphan*/  phy_disconnect (scalar_t__) ; 

__attribute__((used)) static void gmac_uninit(struct net_device *netdev)
{
	if (netdev->phydev)
		phy_disconnect(netdev->phydev);
}