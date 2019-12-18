#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vif_params {int dummy; } ;
struct net_device {TYPE_3__* ieee80211_ptr; int /*<<< orphan*/  name; } ;
struct mwifiex_private {struct mwifiex_adapter* adapter; } ;
struct TYPE_5__ {scalar_t__ uap_intf; int /*<<< orphan*/  sta_intf; int /*<<< orphan*/  p2p_intf; } ;
struct TYPE_4__ {scalar_t__ uap_intf; } ;
struct mwifiex_adapter {TYPE_2__ curr_iface_comb; TYPE_1__ iface_limit; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;
struct TYPE_6__ {int iftype; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HostCmd_ACT_GEN_SET ; 
 int /*<<< orphan*/  HostCmd_CMD_SET_BSS_MODE ; 
 int /*<<< orphan*/  INFO ; 
#define  NL80211_IFTYPE_ADHOC 131 
#define  NL80211_IFTYPE_P2P_CLIENT 130 
#define  NL80211_IFTYPE_P2P_GO 129 
#define  NL80211_IFTYPE_STATION 128 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ mwifiex_deinit_priv_params (struct mwifiex_private*) ; 
 scalar_t__ mwifiex_init_new_priv_params (struct mwifiex_private*,struct net_device*,int) ; 
 struct mwifiex_private* mwifiex_netdev_get_priv (struct net_device*) ; 
 scalar_t__ mwifiex_send_cmd (struct mwifiex_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ mwifiex_sta_init_cmd (struct mwifiex_private*,int,int) ; 

__attribute__((used)) static int
mwifiex_change_vif_to_ap(struct net_device *dev,
			 enum nl80211_iftype curr_iftype,
			 enum nl80211_iftype type,
			 struct vif_params *params)
{
	struct mwifiex_private *priv;
	struct mwifiex_adapter *adapter;

	priv = mwifiex_netdev_get_priv(dev);

	if (!priv)
		return -1;

	adapter = priv->adapter;

	if (adapter->curr_iface_comb.uap_intf ==
	    adapter->iface_limit.uap_intf) {
		mwifiex_dbg(adapter, ERROR,
			    "cannot create multiple AP ifaces\n");
		return -1;
	}

	mwifiex_dbg(adapter, INFO,
		    "%s: changing role to AP\n", dev->name);

	if (mwifiex_deinit_priv_params(priv))
		return -1;
	if (mwifiex_init_new_priv_params(priv, dev, type))
		return -1;
	if (mwifiex_send_cmd(priv, HostCmd_CMD_SET_BSS_MODE,
			     HostCmd_ACT_GEN_SET, 0, NULL, true))
		return -1;
	if (mwifiex_sta_init_cmd(priv, false, false))
		return -1;

	switch (curr_iftype) {
	case NL80211_IFTYPE_P2P_CLIENT:
	case NL80211_IFTYPE_P2P_GO:
		adapter->curr_iface_comb.p2p_intf--;
		break;
	case NL80211_IFTYPE_STATION:
	case NL80211_IFTYPE_ADHOC:
		adapter->curr_iface_comb.sta_intf--;
		break;
	default:
		break;
	}

	adapter->curr_iface_comb.uap_intf++;
	dev->ieee80211_ptr->iftype = type;
	return 0;
}