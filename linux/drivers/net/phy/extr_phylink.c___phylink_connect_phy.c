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
struct phylink {scalar_t__ link_an_mode; int /*<<< orphan*/  netdev; scalar_t__ phydev; } ;
struct phy_device {int dummy; } ;
typedef  int /*<<< orphan*/  phy_interface_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ MLO_AN_FIXED ; 
 scalar_t__ MLO_AN_INBAND ; 
 scalar_t__ WARN_ON (int) ; 
 int phy_attach_direct (int /*<<< orphan*/ ,struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_detach (struct phy_device*) ; 
 scalar_t__ phy_interface_mode_is_8023z (int /*<<< orphan*/ ) ; 
 int phylink_bringup_phy (struct phylink*,struct phy_device*) ; 

__attribute__((used)) static int __phylink_connect_phy(struct phylink *pl, struct phy_device *phy,
		phy_interface_t interface)
{
	int ret;

	if (WARN_ON(pl->link_an_mode == MLO_AN_FIXED ||
		    (pl->link_an_mode == MLO_AN_INBAND &&
		     phy_interface_mode_is_8023z(interface))))
		return -EINVAL;

	if (pl->phydev)
		return -EBUSY;

	ret = phy_attach_direct(pl->netdev, phy, 0, interface);
	if (ret)
		return ret;

	ret = phylink_bringup_phy(pl, phy);
	if (ret)
		phy_detach(phy);

	return ret;
}