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
struct TYPE_5__ {TYPE_3__* wiphy; } ;
struct mwifiex_private {TYPE_2__ wdev; scalar_t__ sched_scanning; } ;
struct mwifiex_ds_hs_cfg {int is_invoke_hostcmd; } ;
struct mwifiex_adapter {int priv_num; int hs_activate_wait_q_woken; int /*<<< orphan*/  hs_activate_wait_q; int /*<<< orphan*/  work_flags; scalar_t__ hs_activated; struct mwifiex_private** priv; } ;
typedef  int /*<<< orphan*/  hscfg ;
struct TYPE_6__ {TYPE_1__* wowlan_config; } ;
struct TYPE_4__ {int /*<<< orphan*/  nd_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD ; 
 int /*<<< orphan*/  ERROR ; 
 int HZ ; 
 int /*<<< orphan*/  HostCmd_ACT_GEN_SET ; 
 int /*<<< orphan*/  MWIFIEX_BSS_ROLE_STA ; 
 int /*<<< orphan*/  MWIFIEX_IS_HS_ENABLING ; 
 int /*<<< orphan*/  MWIFIEX_SYNC_CMD ; 
 int /*<<< orphan*/  cfg80211_sched_scan_stopped (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ disconnect_on_suspend ; 
 int /*<<< orphan*/  memset (struct mwifiex_ds_hs_cfg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mwifiex_cancel_all_pending_cmd (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mwifiex_deauthenticate (struct mwifiex_private*,int /*<<< orphan*/ *) ; 
 struct mwifiex_private* mwifiex_get_priv (struct mwifiex_adapter*,int /*<<< orphan*/ ) ; 
 scalar_t__ mwifiex_set_hs_params (struct mwifiex_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mwifiex_ds_hs_cfg*) ; 
 int /*<<< orphan*/  mwifiex_stop_bg_scan (struct mwifiex_private*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int) ; 

int mwifiex_enable_hs(struct mwifiex_adapter *adapter)
{
	struct mwifiex_ds_hs_cfg hscfg;
	struct mwifiex_private *priv;
	int i;

	if (disconnect_on_suspend) {
		for (i = 0; i < adapter->priv_num; i++) {
			priv = adapter->priv[i];
			if (priv)
				mwifiex_deauthenticate(priv, NULL);
		}
	}

	priv = mwifiex_get_priv(adapter, MWIFIEX_BSS_ROLE_STA);

	if (priv && priv->sched_scanning) {
#ifdef CONFIG_PM
		if (priv->wdev.wiphy->wowlan_config &&
		    !priv->wdev.wiphy->wowlan_config->nd_config) {
#endif
			mwifiex_dbg(adapter, CMD, "aborting bgscan!\n");
			mwifiex_stop_bg_scan(priv);
			cfg80211_sched_scan_stopped(priv->wdev.wiphy, 0);
#ifdef CONFIG_PM
		}
#endif
	}

	if (adapter->hs_activated) {
		mwifiex_dbg(adapter, CMD,
			    "cmd: HS Already activated\n");
		return true;
	}

	adapter->hs_activate_wait_q_woken = false;

	memset(&hscfg, 0, sizeof(hscfg));
	hscfg.is_invoke_hostcmd = true;

	set_bit(MWIFIEX_IS_HS_ENABLING, &adapter->work_flags);
	mwifiex_cancel_all_pending_cmd(adapter);

	if (mwifiex_set_hs_params(mwifiex_get_priv(adapter,
						   MWIFIEX_BSS_ROLE_STA),
				  HostCmd_ACT_GEN_SET, MWIFIEX_SYNC_CMD,
				  &hscfg)) {
		mwifiex_dbg(adapter, ERROR,
			    "IOCTL request HS enable failed\n");
		return false;
	}

	if (wait_event_interruptible_timeout(adapter->hs_activate_wait_q,
					     adapter->hs_activate_wait_q_woken,
					     (10 * HZ)) <= 0) {
		mwifiex_dbg(adapter, ERROR,
			    "hs_activate_wait_q terminated\n");
		return false;
	}

	return true;
}