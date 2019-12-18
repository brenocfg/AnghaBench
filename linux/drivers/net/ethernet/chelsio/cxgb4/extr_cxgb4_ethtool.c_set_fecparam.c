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
struct link_config {int /*<<< orphan*/  requested_fec; } ;
struct port_info {int /*<<< orphan*/  tx_chan; TYPE_1__* adapter; struct link_config link_cfg; } ;
struct net_device {int dummy; } ;
struct ethtool_fecparam {int /*<<< orphan*/  fec; } ;
struct TYPE_2__ {int /*<<< orphan*/  mbox; } ;

/* Variables and functions */
 int /*<<< orphan*/  eth_to_cc_fec (int /*<<< orphan*/ ) ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int t4_link_l1cfg (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct link_config*) ; 

__attribute__((used)) static int set_fecparam(struct net_device *dev, struct ethtool_fecparam *fec)
{
	struct port_info *pi = netdev_priv(dev);
	struct link_config *lc = &pi->link_cfg;
	struct link_config old_lc;
	int ret;

	/* Save old Link Configuration in case the L1 Configure below
	 * fails.
	 */
	old_lc = *lc;

	/* Try to perform the L1 Configure and return the result of that
	 * effort.  If it fails, revert the attempted change.
	 */
	lc->requested_fec = eth_to_cc_fec(fec->fec);
	ret = t4_link_l1cfg(pi->adapter, pi->adapter->mbox,
			    pi->tx_chan, lc);
	if (ret)
		*lc = old_lc;
	return ret;
}