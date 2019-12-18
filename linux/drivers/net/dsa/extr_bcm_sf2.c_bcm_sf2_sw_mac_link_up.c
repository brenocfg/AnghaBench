#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct phy_device {int dummy; } ;
struct ethtool_eee {int /*<<< orphan*/  eee_enabled; } ;
struct dsa_switch {int dummy; } ;
struct bcm_sf2_priv {TYPE_2__* dev; } ;
typedef  int /*<<< orphan*/  phy_interface_t ;
struct TYPE_4__ {TYPE_1__* ports; } ;
struct TYPE_3__ {struct ethtool_eee eee; } ;

/* Variables and functions */
 unsigned int MLO_AN_PHY ; 
 int /*<<< orphan*/  b53_eee_init (struct dsa_switch*,int,struct phy_device*) ; 
 int /*<<< orphan*/  bcm_sf2_sw_mac_link_set (struct dsa_switch*,int,int /*<<< orphan*/ ,int) ; 
 struct bcm_sf2_priv* bcm_sf2_to_priv (struct dsa_switch*) ; 

__attribute__((used)) static void bcm_sf2_sw_mac_link_up(struct dsa_switch *ds, int port,
				   unsigned int mode,
				   phy_interface_t interface,
				   struct phy_device *phydev)
{
	struct bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	struct ethtool_eee *p = &priv->dev->ports[port].eee;

	bcm_sf2_sw_mac_link_set(ds, port, interface, true);

	if (mode == MLO_AN_PHY && phydev)
		p->eee_enabled = b53_eee_init(ds, port, phydev);
}