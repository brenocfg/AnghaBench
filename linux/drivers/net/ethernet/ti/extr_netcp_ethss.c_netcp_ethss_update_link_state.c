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
struct net_device {int dummy; } ;
struct gbe_slave {int slave_num; int /*<<< orphan*/  link_state; int /*<<< orphan*/  open; } ;
struct gbe_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SGMII_BASE (struct gbe_priv*,int) ; 
 scalar_t__ SLAVE_LINK_IS_RGMII (struct gbe_slave*) ; 
 scalar_t__ SLAVE_LINK_IS_SGMII (struct gbe_slave*) ; 
 int atomic_xchg (int /*<<< orphan*/ *,int) ; 
 int gbe_phy_link_status (struct gbe_slave*) ; 
 int /*<<< orphan*/  netcp_2u_rgmii_get_port_link (struct gbe_priv*,int*) ; 
 int /*<<< orphan*/  netcp_ethss_link_state_action (struct gbe_priv*,struct net_device*,struct gbe_slave*,int) ; 
 int netcp_sgmii_get_port_link (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void netcp_ethss_update_link_state(struct gbe_priv *gbe_dev,
					  struct gbe_slave *slave,
					  struct net_device *ndev)
{
	bool sw_link_state = true, phy_link_state;
	int sp = slave->slave_num, link_state;

	if (!slave->open)
		return;

	if (SLAVE_LINK_IS_RGMII(slave))
		netcp_2u_rgmii_get_port_link(gbe_dev,
					     &sw_link_state);
	if (SLAVE_LINK_IS_SGMII(slave))
		sw_link_state =
		netcp_sgmii_get_port_link(SGMII_BASE(gbe_dev, sp), sp);

	phy_link_state = gbe_phy_link_status(slave);
	link_state = phy_link_state & sw_link_state;

	if (atomic_xchg(&slave->link_state, link_state) != link_state)
		netcp_ethss_link_state_action(gbe_dev, ndev, slave,
					      link_state);
}