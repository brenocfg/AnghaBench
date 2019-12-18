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
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int flags; } ;
struct fsl_mc_io {int dummy; } ;
struct TYPE_2__ {int mac_filter_entries; int options; } ;
struct dpaa2_eth_priv {struct fsl_mc_io* mc_io; int /*<<< orphan*/  mc_token; TYPE_1__ dpni_attrs; } ;

/* Variables and functions */
 int DPNI_OPT_NO_MAC_FILTER ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  add_mc_hw_addr (struct net_device*,struct dpaa2_eth_priv*) ; 
 int /*<<< orphan*/  add_uc_hw_addr (struct net_device*,struct dpaa2_eth_priv*) ; 
 int dpni_clear_mac_filters (struct fsl_mc_io*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int dpni_set_multicast_promisc (struct fsl_mc_io*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int dpni_set_unicast_promisc (struct fsl_mc_io*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int,...) ; 
 int netdev_mc_count (struct net_device*) ; 
 struct dpaa2_eth_priv* netdev_priv (struct net_device*) ; 
 int netdev_uc_count (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,...) ; 

__attribute__((used)) static void dpaa2_eth_set_rx_mode(struct net_device *net_dev)
{
	struct dpaa2_eth_priv *priv = netdev_priv(net_dev);
	int uc_count = netdev_uc_count(net_dev);
	int mc_count = netdev_mc_count(net_dev);
	u8 max_mac = priv->dpni_attrs.mac_filter_entries;
	u32 options = priv->dpni_attrs.options;
	u16 mc_token = priv->mc_token;
	struct fsl_mc_io *mc_io = priv->mc_io;
	int err;

	/* Basic sanity checks; these probably indicate a misconfiguration */
	if (options & DPNI_OPT_NO_MAC_FILTER && max_mac != 0)
		netdev_info(net_dev,
			    "mac_filter_entries=%d, DPNI_OPT_NO_MAC_FILTER option must be disabled\n",
			    max_mac);

	/* Force promiscuous if the uc or mc counts exceed our capabilities. */
	if (uc_count > max_mac) {
		netdev_info(net_dev,
			    "Unicast addr count reached %d, max allowed is %d; forcing promisc\n",
			    uc_count, max_mac);
		goto force_promisc;
	}
	if (mc_count + uc_count > max_mac) {
		netdev_info(net_dev,
			    "Unicast + multicast addr count reached %d, max allowed is %d; forcing promisc\n",
			    uc_count + mc_count, max_mac);
		goto force_mc_promisc;
	}

	/* Adjust promisc settings due to flag combinations */
	if (net_dev->flags & IFF_PROMISC)
		goto force_promisc;
	if (net_dev->flags & IFF_ALLMULTI) {
		/* First, rebuild unicast filtering table. This should be done
		 * in promisc mode, in order to avoid frame loss while we
		 * progressively add entries to the table.
		 * We don't know whether we had been in promisc already, and
		 * making an MC call to find out is expensive; so set uc promisc
		 * nonetheless.
		 */
		err = dpni_set_unicast_promisc(mc_io, 0, mc_token, 1);
		if (err)
			netdev_warn(net_dev, "Can't set uc promisc\n");

		/* Actual uc table reconstruction. */
		err = dpni_clear_mac_filters(mc_io, 0, mc_token, 1, 0);
		if (err)
			netdev_warn(net_dev, "Can't clear uc filters\n");
		add_uc_hw_addr(net_dev, priv);

		/* Finally, clear uc promisc and set mc promisc as requested. */
		err = dpni_set_unicast_promisc(mc_io, 0, mc_token, 0);
		if (err)
			netdev_warn(net_dev, "Can't clear uc promisc\n");
		goto force_mc_promisc;
	}

	/* Neither unicast, nor multicast promisc will be on... eventually.
	 * For now, rebuild mac filtering tables while forcing both of them on.
	 */
	err = dpni_set_unicast_promisc(mc_io, 0, mc_token, 1);
	if (err)
		netdev_warn(net_dev, "Can't set uc promisc (%d)\n", err);
	err = dpni_set_multicast_promisc(mc_io, 0, mc_token, 1);
	if (err)
		netdev_warn(net_dev, "Can't set mc promisc (%d)\n", err);

	/* Actual mac filtering tables reconstruction */
	err = dpni_clear_mac_filters(mc_io, 0, mc_token, 1, 1);
	if (err)
		netdev_warn(net_dev, "Can't clear mac filters\n");
	add_mc_hw_addr(net_dev, priv);
	add_uc_hw_addr(net_dev, priv);

	/* Now we can clear both ucast and mcast promisc, without risking
	 * to drop legitimate frames anymore.
	 */
	err = dpni_set_unicast_promisc(mc_io, 0, mc_token, 0);
	if (err)
		netdev_warn(net_dev, "Can't clear ucast promisc\n");
	err = dpni_set_multicast_promisc(mc_io, 0, mc_token, 0);
	if (err)
		netdev_warn(net_dev, "Can't clear mcast promisc\n");

	return;

force_promisc:
	err = dpni_set_unicast_promisc(mc_io, 0, mc_token, 1);
	if (err)
		netdev_warn(net_dev, "Can't set ucast promisc\n");
force_mc_promisc:
	err = dpni_set_multicast_promisc(mc_io, 0, mc_token, 1);
	if (err)
		netdev_warn(net_dev, "Can't set mcast promisc\n");
}