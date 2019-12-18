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
struct wireless_dev {int iftype; struct wiphy* wiphy; } ;
struct wiphy {TYPE_1__** bands; } ;
struct vif_params {int dummy; } ;
struct net_device {int flags; int /*<<< orphan*/  name; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/  hard_header_len; int /*<<< orphan*/  watchdog_timeo; struct wireless_dev* ieee80211_ptr; } ;
struct mwifiex_private {int bss_mode; struct wireless_dev wdev; struct net_device* netdev; int /*<<< orphan*/ * dfs_cac_workqueue; int /*<<< orphan*/ * dfs_chan_sw_workqueue; int /*<<< orphan*/  async_mutex; int /*<<< orphan*/  dfs_chan_sw_work; int /*<<< orphan*/  dfs_cac_work; int /*<<< orphan*/  bss_started; void* bss_role; void* bss_priority; void* frame_type; void* bss_type; } ;
struct TYPE_5__ {int /*<<< orphan*/  p2p_intf; int /*<<< orphan*/  uap_intf; int /*<<< orphan*/  sta_intf; } ;
struct TYPE_6__ {int /*<<< orphan*/  p2p_intf; int /*<<< orphan*/  uap_intf; int /*<<< orphan*/  sta_intf; } ;
struct mwifiex_adapter {int config_bands; TYPE_2__ curr_iface_comb; int /*<<< orphan*/  dev; scalar_t__ is_hw_11ac_capable; int /*<<< orphan*/  mfg_mode; TYPE_3__ iface_limit; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;
struct TYPE_4__ {int /*<<< orphan*/  vht_cap; int /*<<< orphan*/  ht_cap; } ;

/* Variables and functions */
 int BAND_A ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ERROR ; 
 struct wireless_dev* ERR_PTR (int) ; 
 int /*<<< orphan*/  HostCmd_ACT_GEN_SET ; 
 int /*<<< orphan*/  HostCmd_CMD_SET_BSS_MODE ; 
 int /*<<< orphan*/  IEEE80211_NUM_ACS ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* MWIFIEX_BSS_ROLE_STA ; 
 void* MWIFIEX_BSS_ROLE_UAP ; 
 void* MWIFIEX_BSS_TYPE_P2P ; 
 void* MWIFIEX_BSS_TYPE_STA ; 
 void* MWIFIEX_BSS_TYPE_UAP ; 
 void* MWIFIEX_DATA_FRAME_TYPE_ETH_II ; 
 int /*<<< orphan*/  MWIFIEX_DEFAULT_WATCHDOG_TIMEOUT ; 
 scalar_t__ MWIFIEX_MIN_DATA_HEADER_LEN ; 
 size_t NL80211_BAND_2GHZ ; 
 size_t NL80211_BAND_5GHZ ; 
#define  NL80211_IFTYPE_ADHOC 132 
#define  NL80211_IFTYPE_AP 131 
#define  NL80211_IFTYPE_P2P_CLIENT 130 
#define  NL80211_IFTYPE_STATION 129 
#define  NL80211_IFTYPE_UNSPECIFIED 128 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ ) ; 
 int WQ_HIGHPRI ; 
 int WQ_MEM_RECLAIM ; 
 int WQ_UNBOUND ; 
 struct net_device* alloc_netdev_mqs (int,char const*,unsigned char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* alloc_workqueue (char*,int,int,char const*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_net_set (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_setup ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  memset (struct wireless_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct mwifiex_adapter* mwifiex_cfg80211_get_adapter (struct wiphy*) ; 
 int /*<<< orphan*/  mwifiex_cfg80211_init_p2p_client (struct mwifiex_private*) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mwifiex_dev_debugfs_init (struct mwifiex_private*) ; 
 int /*<<< orphan*/  mwifiex_dfs_cac_work_queue ; 
 int /*<<< orphan*/  mwifiex_dfs_chan_sw_work_queue ; 
 int /*<<< orphan*/  mwifiex_ethtool_ops ; 
 struct mwifiex_private* mwifiex_get_unused_priv_by_bss_type (struct mwifiex_adapter*,void*) ; 
 int /*<<< orphan*/  mwifiex_init_priv_params (struct mwifiex_private*,struct net_device*) ; 
 int mwifiex_send_cmd (struct mwifiex_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mwifiex_set_mac_address (struct mwifiex_private*,struct net_device*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mwifiex_setup_ht_caps (int /*<<< orphan*/ *,struct mwifiex_private*) ; 
 int /*<<< orphan*/  mwifiex_setup_vht_caps (int /*<<< orphan*/ *,struct mwifiex_private*) ; 
 int mwifiex_sta_init_cmd (struct mwifiex_private*,int,int) ; 
 void* netdev_priv (struct net_device*) ; 
 scalar_t__ register_netdevice (struct net_device*) ; 
 int /*<<< orphan*/  wiphy_dev (struct wiphy*) ; 
 int /*<<< orphan*/  wiphy_net (struct wiphy*) ; 

struct wireless_dev *mwifiex_add_virtual_intf(struct wiphy *wiphy,
					      const char *name,
					      unsigned char name_assign_type,
					      enum nl80211_iftype type,
					      struct vif_params *params)
{
	struct mwifiex_adapter *adapter = mwifiex_cfg80211_get_adapter(wiphy);
	struct mwifiex_private *priv;
	struct net_device *dev;
	void *mdev_priv;
	int ret;

	if (!adapter)
		return ERR_PTR(-EFAULT);

	switch (type) {
	case NL80211_IFTYPE_UNSPECIFIED:
	case NL80211_IFTYPE_STATION:
	case NL80211_IFTYPE_ADHOC:
		if (adapter->curr_iface_comb.sta_intf ==
		    adapter->iface_limit.sta_intf) {
			mwifiex_dbg(adapter, ERROR,
				    "cannot create multiple sta/adhoc ifaces\n");
			return ERR_PTR(-EINVAL);
		}

		priv = mwifiex_get_unused_priv_by_bss_type(
						adapter, MWIFIEX_BSS_TYPE_STA);
		if (!priv) {
			mwifiex_dbg(adapter, ERROR,
				    "could not get free private struct\n");
			return ERR_PTR(-EFAULT);
		}

		priv->wdev.wiphy = wiphy;
		priv->wdev.iftype = NL80211_IFTYPE_STATION;

		if (type == NL80211_IFTYPE_UNSPECIFIED)
			priv->bss_mode = NL80211_IFTYPE_STATION;
		else
			priv->bss_mode = type;

		priv->bss_type = MWIFIEX_BSS_TYPE_STA;
		priv->frame_type = MWIFIEX_DATA_FRAME_TYPE_ETH_II;
		priv->bss_priority = 0;
		priv->bss_role = MWIFIEX_BSS_ROLE_STA;

		break;
	case NL80211_IFTYPE_AP:
		if (adapter->curr_iface_comb.uap_intf ==
		    adapter->iface_limit.uap_intf) {
			mwifiex_dbg(adapter, ERROR,
				    "cannot create multiple AP ifaces\n");
			return ERR_PTR(-EINVAL);
		}

		priv = mwifiex_get_unused_priv_by_bss_type(
						adapter, MWIFIEX_BSS_TYPE_UAP);
		if (!priv) {
			mwifiex_dbg(adapter, ERROR,
				    "could not get free private struct\n");
			return ERR_PTR(-EFAULT);
		}

		priv->wdev.wiphy = wiphy;
		priv->wdev.iftype = NL80211_IFTYPE_AP;

		priv->bss_type = MWIFIEX_BSS_TYPE_UAP;
		priv->frame_type = MWIFIEX_DATA_FRAME_TYPE_ETH_II;
		priv->bss_priority = 0;
		priv->bss_role = MWIFIEX_BSS_ROLE_UAP;
		priv->bss_started = 0;
		priv->bss_mode = type;

		break;
	case NL80211_IFTYPE_P2P_CLIENT:
		if (adapter->curr_iface_comb.p2p_intf ==
		    adapter->iface_limit.p2p_intf) {
			mwifiex_dbg(adapter, ERROR,
				    "cannot create multiple P2P ifaces\n");
			return ERR_PTR(-EINVAL);
		}

		priv = mwifiex_get_unused_priv_by_bss_type(
						adapter, MWIFIEX_BSS_TYPE_P2P);
		if (!priv) {
			mwifiex_dbg(adapter, ERROR,
				    "could not get free private struct\n");
			return ERR_PTR(-EFAULT);
		}

		priv->wdev.wiphy = wiphy;
		/* At start-up, wpa_supplicant tries to change the interface
		 * to NL80211_IFTYPE_STATION if it is not managed mode.
		 */
		priv->wdev.iftype = NL80211_IFTYPE_P2P_CLIENT;
		priv->bss_mode = NL80211_IFTYPE_P2P_CLIENT;

		/* Setting bss_type to P2P tells firmware that this interface
		 * is receiving P2P peers found during find phase and doing
		 * action frame handshake.
		 */
		priv->bss_type = MWIFIEX_BSS_TYPE_P2P;

		priv->frame_type = MWIFIEX_DATA_FRAME_TYPE_ETH_II;
		priv->bss_priority = MWIFIEX_BSS_ROLE_STA;
		priv->bss_role = MWIFIEX_BSS_ROLE_STA;
		priv->bss_started = 0;

		if (mwifiex_cfg80211_init_p2p_client(priv)) {
			memset(&priv->wdev, 0, sizeof(priv->wdev));
			priv->wdev.iftype = NL80211_IFTYPE_UNSPECIFIED;
			return ERR_PTR(-EFAULT);
		}

		break;
	default:
		mwifiex_dbg(adapter, ERROR, "type not supported\n");
		return ERR_PTR(-EINVAL);
	}

	dev = alloc_netdev_mqs(sizeof(struct mwifiex_private *), name,
			       name_assign_type, ether_setup,
			       IEEE80211_NUM_ACS, 1);
	if (!dev) {
		mwifiex_dbg(adapter, ERROR,
			    "no memory available for netdevice\n");
		ret = -ENOMEM;
		goto err_alloc_netdev;
	}

	mwifiex_init_priv_params(priv, dev);

	priv->netdev = dev;

	if (!adapter->mfg_mode) {
		mwifiex_set_mac_address(priv, dev, false, NULL);

		ret = mwifiex_send_cmd(priv, HostCmd_CMD_SET_BSS_MODE,
				       HostCmd_ACT_GEN_SET, 0, NULL, true);
		if (ret)
			goto err_set_bss_mode;

		ret = mwifiex_sta_init_cmd(priv, false, false);
		if (ret)
			goto err_sta_init;
	}

	mwifiex_setup_ht_caps(&wiphy->bands[NL80211_BAND_2GHZ]->ht_cap, priv);
	if (adapter->is_hw_11ac_capable)
		mwifiex_setup_vht_caps(
			&wiphy->bands[NL80211_BAND_2GHZ]->vht_cap, priv);

	if (adapter->config_bands & BAND_A)
		mwifiex_setup_ht_caps(
			&wiphy->bands[NL80211_BAND_5GHZ]->ht_cap, priv);

	if ((adapter->config_bands & BAND_A) && adapter->is_hw_11ac_capable)
		mwifiex_setup_vht_caps(
			&wiphy->bands[NL80211_BAND_5GHZ]->vht_cap, priv);

	dev_net_set(dev, wiphy_net(wiphy));
	dev->ieee80211_ptr = &priv->wdev;
	dev->ieee80211_ptr->iftype = priv->bss_mode;
	SET_NETDEV_DEV(dev, wiphy_dev(wiphy));

	dev->flags |= IFF_BROADCAST | IFF_MULTICAST;
	dev->watchdog_timeo = MWIFIEX_DEFAULT_WATCHDOG_TIMEOUT;
	dev->hard_header_len += MWIFIEX_MIN_DATA_HEADER_LEN;
	dev->ethtool_ops = &mwifiex_ethtool_ops;

	mdev_priv = netdev_priv(dev);
	*((unsigned long *) mdev_priv) = (unsigned long) priv;

	SET_NETDEV_DEV(dev, adapter->dev);

	priv->dfs_cac_workqueue = alloc_workqueue("MWIFIEX_DFS_CAC%s",
						  WQ_HIGHPRI |
						  WQ_MEM_RECLAIM |
						  WQ_UNBOUND, 1, name);
	if (!priv->dfs_cac_workqueue) {
		mwifiex_dbg(adapter, ERROR, "cannot alloc DFS CAC queue\n");
		ret = -ENOMEM;
		goto err_alloc_cac;
	}

	INIT_DELAYED_WORK(&priv->dfs_cac_work, mwifiex_dfs_cac_work_queue);

	priv->dfs_chan_sw_workqueue = alloc_workqueue("MWIFIEX_DFS_CHSW%s",
						      WQ_HIGHPRI | WQ_UNBOUND |
						      WQ_MEM_RECLAIM, 1, name);
	if (!priv->dfs_chan_sw_workqueue) {
		mwifiex_dbg(adapter, ERROR, "cannot alloc DFS channel sw queue\n");
		ret = -ENOMEM;
		goto err_alloc_chsw;
	}

	INIT_DELAYED_WORK(&priv->dfs_chan_sw_work,
			  mwifiex_dfs_chan_sw_work_queue);

	mutex_init(&priv->async_mutex);

	/* Register network device */
	if (register_netdevice(dev)) {
		mwifiex_dbg(adapter, ERROR, "cannot register network device\n");
		ret = -EFAULT;
		goto err_reg_netdev;
	}

	mwifiex_dbg(adapter, INFO,
		    "info: %s: Marvell 802.11 Adapter\n", dev->name);

#ifdef CONFIG_DEBUG_FS
	mwifiex_dev_debugfs_init(priv);
#endif

	switch (type) {
	case NL80211_IFTYPE_UNSPECIFIED:
	case NL80211_IFTYPE_STATION:
	case NL80211_IFTYPE_ADHOC:
		adapter->curr_iface_comb.sta_intf++;
		break;
	case NL80211_IFTYPE_AP:
		adapter->curr_iface_comb.uap_intf++;
		break;
	case NL80211_IFTYPE_P2P_CLIENT:
		adapter->curr_iface_comb.p2p_intf++;
		break;
	default:
		/* This should be dead code; checked above */
		mwifiex_dbg(adapter, ERROR, "type not supported\n");
		return ERR_PTR(-EINVAL);
	}

	return &priv->wdev;

err_reg_netdev:
	destroy_workqueue(priv->dfs_chan_sw_workqueue);
	priv->dfs_chan_sw_workqueue = NULL;
err_alloc_chsw:
	destroy_workqueue(priv->dfs_cac_workqueue);
	priv->dfs_cac_workqueue = NULL;
err_alloc_cac:
	free_netdev(dev);
	priv->netdev = NULL;
err_sta_init:
err_set_bss_mode:
err_alloc_netdev:
	memset(&priv->wdev, 0, sizeof(priv->wdev));
	priv->wdev.iftype = NL80211_IFTYPE_UNSPECIFIED;
	priv->bss_mode = NL80211_IFTYPE_UNSPECIFIED;
	return ERR_PTR(ret);
}