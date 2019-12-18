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
struct TYPE_2__ {scalar_t__ cac_started; } ;
struct mwifiex_private {int /*<<< orphan*/  dfs_chandef; int /*<<< orphan*/  netdev; int /*<<< orphan*/  dfs_cac_work; int /*<<< orphan*/  adapter; TYPE_1__ wdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MSG ; 
 int /*<<< orphan*/  NL80211_RADAR_CAC_ABORTED ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfg80211_cac_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mwifiex_stop_radar_detection (struct mwifiex_private*,int /*<<< orphan*/ *) ; 

void mwifiex_abort_cac(struct mwifiex_private *priv)
{
	if (priv->wdev.cac_started) {
		if (mwifiex_stop_radar_detection(priv, &priv->dfs_chandef))
			mwifiex_dbg(priv->adapter, ERROR,
				    "failed to stop CAC in FW\n");
		mwifiex_dbg(priv->adapter, MSG,
			    "Aborting delayed work for CAC.\n");
		cancel_delayed_work_sync(&priv->dfs_cac_work);
		cfg80211_cac_event(priv->netdev, &priv->dfs_chandef,
				   NL80211_RADAR_CAC_ABORTED, GFP_KERNEL);
	}
}