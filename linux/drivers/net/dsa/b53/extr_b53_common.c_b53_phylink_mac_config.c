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
struct phylink_link_state {scalar_t__ interface; int /*<<< orphan*/  pause; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct dsa_switch {struct b53_device* priv; } ;
struct b53_device {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* serdes_config ) (struct b53_device*,int,unsigned int,struct phylink_link_state const*) ;} ;

/* Variables and functions */
 unsigned int MLO_AN_FIXED ; 
 unsigned int MLO_AN_PHY ; 
 scalar_t__ PHY_INTERFACE_MODE_SGMII ; 
 int /*<<< orphan*/  b53_force_port_config (struct b53_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ phy_interface_mode_is_8023z (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct b53_device*,int,unsigned int,struct phylink_link_state const*) ; 

void b53_phylink_mac_config(struct dsa_switch *ds, int port,
			    unsigned int mode,
			    const struct phylink_link_state *state)
{
	struct b53_device *dev = ds->priv;

	if (mode == MLO_AN_PHY)
		return;

	if (mode == MLO_AN_FIXED) {
		b53_force_port_config(dev, port, state->speed,
				      state->duplex, state->pause);
		return;
	}

	if ((phy_interface_mode_is_8023z(state->interface) ||
	     state->interface == PHY_INTERFACE_MODE_SGMII) &&
	     dev->ops->serdes_config)
		dev->ops->serdes_config(dev, port, mode, state);
}