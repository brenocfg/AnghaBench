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
struct phylink_link_state {scalar_t__ interface; } ;
struct dsa_switch {struct b53_device* priv; } ;
struct b53_device {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* serdes_link_state ) (struct b53_device*,int,struct phylink_link_state*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ PHY_INTERFACE_MODE_SGMII ; 
 scalar_t__ phy_interface_mode_is_8023z (scalar_t__) ; 
 int stub1 (struct b53_device*,int,struct phylink_link_state*) ; 

int b53_phylink_mac_link_state(struct dsa_switch *ds, int port,
			       struct phylink_link_state *state)
{
	struct b53_device *dev = ds->priv;
	int ret = -EOPNOTSUPP;

	if ((phy_interface_mode_is_8023z(state->interface) ||
	     state->interface == PHY_INTERFACE_MODE_SGMII) &&
	     dev->ops->serdes_link_state)
		ret = dev->ops->serdes_link_state(dev, port, state);

	return ret;
}