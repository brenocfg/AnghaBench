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
struct TYPE_4__ {int /*<<< orphan*/  authentication_mode; } ;
struct TYPE_3__ {void* iftype; } ;
struct mwifiex_private {TYPE_2__ sec_info; void* bss_mode; TYPE_1__ wdev; scalar_t__ mgmt_frame_mask; struct mwifiex_adapter* adapter; } ;
struct mwifiex_adapter {int main_locked; int rx_locked; int /*<<< orphan*/  rx_proc_lock; int /*<<< orphan*/  rx_workqueue; scalar_t__ rx_processing; int /*<<< orphan*/  main_proc_lock; int /*<<< orphan*/  workqueue; scalar_t__ mwifiex_processing; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HostCmd_ACT_GEN_SET ; 
 int /*<<< orphan*/  HostCmd_CMD_MGMT_FRAME_REG ; 
 int /*<<< orphan*/  NL80211_AUTHTYPE_OPEN_SYSTEM ; 
 void* NL80211_IFTYPE_UNSPECIFIED ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mwifiex_deauthenticate (struct mwifiex_private*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mwifiex_free_priv (struct mwifiex_private*) ; 
 scalar_t__ mwifiex_send_cmd (struct mwifiex_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int mwifiex_deinit_priv_params(struct mwifiex_private *priv)
{
	struct mwifiex_adapter *adapter = priv->adapter;
	unsigned long flags;

	priv->mgmt_frame_mask = 0;
	if (mwifiex_send_cmd(priv, HostCmd_CMD_MGMT_FRAME_REG,
			     HostCmd_ACT_GEN_SET, 0,
			     &priv->mgmt_frame_mask, false)) {
		mwifiex_dbg(adapter, ERROR,
			    "could not unregister mgmt frame rx\n");
		return -1;
	}

	mwifiex_deauthenticate(priv, NULL);

	spin_lock_irqsave(&adapter->main_proc_lock, flags);
	adapter->main_locked = true;
	if (adapter->mwifiex_processing) {
		spin_unlock_irqrestore(&adapter->main_proc_lock, flags);
		flush_workqueue(adapter->workqueue);
	} else {
		spin_unlock_irqrestore(&adapter->main_proc_lock, flags);
	}

	spin_lock_bh(&adapter->rx_proc_lock);
	adapter->rx_locked = true;
	if (adapter->rx_processing) {
		spin_unlock_bh(&adapter->rx_proc_lock);
		flush_workqueue(adapter->rx_workqueue);
	} else {
	spin_unlock_bh(&adapter->rx_proc_lock);
	}

	mwifiex_free_priv(priv);
	priv->wdev.iftype = NL80211_IFTYPE_UNSPECIFIED;
	priv->bss_mode = NL80211_IFTYPE_UNSPECIFIED;
	priv->sec_info.authentication_mode = NL80211_AUTHTYPE_OPEN_SYSTEM;

	return 0;
}