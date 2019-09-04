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
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int phy_start_aneg (scalar_t__) ; 

__attribute__((used)) static int octeon_mgmt_nway_reset(struct net_device *dev)
{
	if (!capable(CAP_NET_ADMIN))
		return -EPERM;

	if (dev->phydev)
		return phy_start_aneg(dev->phydev);

	return -EOPNOTSUPP;
}