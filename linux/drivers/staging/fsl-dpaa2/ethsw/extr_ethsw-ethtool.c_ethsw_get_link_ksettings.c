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
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  speed; int /*<<< orphan*/  duplex; int /*<<< orphan*/  autoneg; } ;
struct ethtool_link_ksettings {TYPE_2__ base; } ;
struct ethsw_port_priv {int /*<<< orphan*/  idx; TYPE_1__* ethsw_data; } ;
struct dpsw_link_state {int options; int /*<<< orphan*/  rate; int /*<<< orphan*/  member_0; } ;
struct TYPE_3__ {int /*<<< orphan*/  dpsw_handle; int /*<<< orphan*/  mc_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int DPSW_LINK_OPT_AUTONEG ; 
 int DPSW_LINK_OPT_HALF_DUPLEX ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int dpsw_if_get_link_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dpsw_link_state*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 struct ethsw_port_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
ethsw_get_link_ksettings(struct net_device *netdev,
			 struct ethtool_link_ksettings *link_ksettings)
{
	struct ethsw_port_priv *port_priv = netdev_priv(netdev);
	struct dpsw_link_state state = {0};
	int err = 0;

	err = dpsw_if_get_link_state(port_priv->ethsw_data->mc_io, 0,
				     port_priv->ethsw_data->dpsw_handle,
				     port_priv->idx,
				     &state);
	if (err) {
		netdev_err(netdev, "ERROR %d getting link state\n", err);
		goto out;
	}

	/* At the moment, we have no way of interrogating the DPMAC
	 * from the DPSW side or there may not exist a DPMAC at all.
	 * Report only autoneg state, duplexity and speed.
	 */
	if (state.options & DPSW_LINK_OPT_AUTONEG)
		link_ksettings->base.autoneg = AUTONEG_ENABLE;
	if (!(state.options & DPSW_LINK_OPT_HALF_DUPLEX))
		link_ksettings->base.duplex = DUPLEX_FULL;
	link_ksettings->base.speed = state.rate;

out:
	return err;
}