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
struct link_config {unsigned int pcaps; unsigned int speed_caps; unsigned int acaps; scalar_t__ autoneg; } ;
struct port_info {int /*<<< orphan*/  tx_chan; TYPE_2__* adapter; struct link_config link_cfg; } ;
struct net_device {int dummy; } ;
struct ethtool_link_settings {scalar_t__ duplex; scalar_t__ autoneg; int /*<<< orphan*/  speed; } ;
struct TYPE_3__ {int /*<<< orphan*/  advertising; } ;
struct ethtool_link_ksettings {TYPE_1__ link_modes; struct ethtool_link_settings base; } ;
struct TYPE_4__ {int /*<<< orphan*/  mbox; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_DISABLE ; 
 scalar_t__ DUPLEX_FULL ; 
 int EINVAL ; 
 unsigned int FW_PORT_CAP32_ANEG ; 
 unsigned int lmm_to_fw_caps (int /*<<< orphan*/ ) ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 unsigned int speed_to_fw_caps (int /*<<< orphan*/ ) ; 
 int t4_link_l1cfg (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct link_config*) ; 

__attribute__((used)) static int set_link_ksettings(struct net_device *dev,
			    const struct ethtool_link_ksettings *link_ksettings)
{
	struct port_info *pi = netdev_priv(dev);
	struct link_config *lc = &pi->link_cfg;
	const struct ethtool_link_settings *base = &link_ksettings->base;
	struct link_config old_lc;
	unsigned int fw_caps;
	int ret = 0;

	/* only full-duplex supported */
	if (base->duplex != DUPLEX_FULL)
		return -EINVAL;

	old_lc = *lc;
	if (!(lc->pcaps & FW_PORT_CAP32_ANEG) ||
	    base->autoneg == AUTONEG_DISABLE) {
		fw_caps = speed_to_fw_caps(base->speed);

		/* Speed must be supported by Physical Port Capabilities. */
		if (!(lc->pcaps & fw_caps))
			return -EINVAL;

		lc->speed_caps = fw_caps;
		lc->acaps = fw_caps;
	} else {
		fw_caps =
			lmm_to_fw_caps(link_ksettings->link_modes.advertising);
		if (!(lc->pcaps & fw_caps))
			return -EINVAL;
		lc->speed_caps = 0;
		lc->acaps = fw_caps | FW_PORT_CAP32_ANEG;
	}
	lc->autoneg = base->autoneg;

	/* If the firmware rejects the Link Configuration request, back out
	 * the changes and report the error.
	 */
	ret = t4_link_l1cfg(pi->adapter, pi->adapter->mbox, pi->tx_chan, lc);
	if (ret)
		*lc = old_lc;

	return ret;
}