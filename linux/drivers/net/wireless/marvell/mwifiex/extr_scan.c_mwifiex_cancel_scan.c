#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mwifiex_private {int scan_aborting; int /*<<< orphan*/ * scan_request; } ;
struct mwifiex_adapter {int scan_processing; int priv_num; struct mwifiex_private** priv; int /*<<< orphan*/  mwifiex_cmd_lock; } ;
struct cfg80211_scan_info {int aborted; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  cfg80211_scan_done (int /*<<< orphan*/ *,struct cfg80211_scan_info*) ; 
 int /*<<< orphan*/  mwifiex_cancel_pending_scan_cmd (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void mwifiex_cancel_scan(struct mwifiex_adapter *adapter)
{
	struct mwifiex_private *priv;
	int i;

	mwifiex_cancel_pending_scan_cmd(adapter);

	if (adapter->scan_processing) {
		spin_lock_bh(&adapter->mwifiex_cmd_lock);
		adapter->scan_processing = false;
		spin_unlock_bh(&adapter->mwifiex_cmd_lock);
		for (i = 0; i < adapter->priv_num; i++) {
			priv = adapter->priv[i];
			if (!priv)
				continue;
			if (priv->scan_request) {
				struct cfg80211_scan_info info = {
					.aborted = true,
				};

				mwifiex_dbg(adapter, INFO,
					    "info: aborting scan\n");
				cfg80211_scan_done(priv->scan_request, &info);
				priv->scan_request = NULL;
				priv->scan_aborting = false;
			}
		}
	}
}