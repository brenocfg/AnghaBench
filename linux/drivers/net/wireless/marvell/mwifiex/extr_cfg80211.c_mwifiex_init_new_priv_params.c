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
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int iftype; } ;
struct mwifiex_private {int bss_mode; void* bss_role; scalar_t__ bss_started; int /*<<< orphan*/  netdev; TYPE_1__ wdev; struct mwifiex_adapter* adapter; } ;
struct mwifiex_adapter {int main_locked; int rx_locked; int /*<<< orphan*/  rx_proc_lock; int /*<<< orphan*/  main_proc_lock; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ERROR ; 
 void* MWIFIEX_BSS_ROLE_STA ; 
 void* MWIFIEX_BSS_ROLE_UAP ; 
#define  NL80211_IFTYPE_ADHOC 132 
#define  NL80211_IFTYPE_AP 131 
#define  NL80211_IFTYPE_P2P_CLIENT 130 
#define  NL80211_IFTYPE_P2P_GO 129 
#define  NL80211_IFTYPE_STATION 128 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mwifiex_init_priv (struct mwifiex_private*) ; 
 int /*<<< orphan*/  mwifiex_init_priv_params (struct mwifiex_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_set_mac_address (struct mwifiex_private*,struct net_device*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
mwifiex_init_new_priv_params(struct mwifiex_private *priv,
			     struct net_device *dev,
			     enum nl80211_iftype type)
{
	struct mwifiex_adapter *adapter = priv->adapter;
	unsigned long flags;

	mwifiex_init_priv(priv);

	priv->bss_mode = type;
	priv->wdev.iftype = type;

	mwifiex_init_priv_params(priv, priv->netdev);
	priv->bss_started = 0;

	switch (type) {
	case NL80211_IFTYPE_STATION:
	case NL80211_IFTYPE_ADHOC:
		priv->bss_role =  MWIFIEX_BSS_ROLE_STA;
		break;
	case NL80211_IFTYPE_P2P_CLIENT:
		priv->bss_role =  MWIFIEX_BSS_ROLE_STA;
		break;
	case NL80211_IFTYPE_P2P_GO:
		priv->bss_role =  MWIFIEX_BSS_ROLE_UAP;
		break;
	case NL80211_IFTYPE_AP:
		priv->bss_role = MWIFIEX_BSS_ROLE_UAP;
		break;
	default:
		mwifiex_dbg(adapter, ERROR,
			    "%s: changing to %d not supported\n",
			    dev->name, type);
		return -EOPNOTSUPP;
	}

	spin_lock_irqsave(&adapter->main_proc_lock, flags);
	adapter->main_locked = false;
	spin_unlock_irqrestore(&adapter->main_proc_lock, flags);

	spin_lock_bh(&adapter->rx_proc_lock);
	adapter->rx_locked = false;
	spin_unlock_bh(&adapter->rx_proc_lock);

	mwifiex_set_mac_address(priv, dev, false, NULL);

	return 0;
}