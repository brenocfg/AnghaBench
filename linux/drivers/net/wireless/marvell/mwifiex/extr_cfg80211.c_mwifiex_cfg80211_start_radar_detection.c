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
typedef  int /*<<< orphan*/  u32 ;
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct mwifiex_radar_params {int /*<<< orphan*/  cac_time_ms; struct cfg80211_chan_def* chandef; } ;
struct TYPE_3__ {int is_11h_active; } ;
struct mwifiex_private {int /*<<< orphan*/  dfs_cac_work; int /*<<< orphan*/  dfs_cac_workqueue; int /*<<< orphan*/  dfs_chandef; TYPE_1__ state_11h; TYPE_2__* adapter; } ;
struct cfg80211_chan_def {int dummy; } ;
struct TYPE_4__ {scalar_t__ scan_processing; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HostCmd_ACT_GEN_SET ; 
 int /*<<< orphan*/  HostCmd_CMD_CHAN_REPORT_REQUEST ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct cfg80211_chan_def*,int) ; 
 int /*<<< orphan*/  memset (struct mwifiex_radar_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ mwifiex_11h_activate (struct mwifiex_private*,int) ; 
 int /*<<< orphan*/  mwifiex_dbg (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mwifiex_is_11h_active (struct mwifiex_private*) ; 
 struct mwifiex_private* mwifiex_netdev_get_priv (struct net_device*) ; 
 scalar_t__ mwifiex_send_cmd (struct mwifiex_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mwifiex_radar_params*,int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mwifiex_cfg80211_start_radar_detection(struct wiphy *wiphy,
				       struct net_device *dev,
				       struct cfg80211_chan_def *chandef,
				       u32 cac_time_ms)
{
	struct mwifiex_private *priv = mwifiex_netdev_get_priv(dev);
	struct mwifiex_radar_params radar_params;

	if (priv->adapter->scan_processing) {
		mwifiex_dbg(priv->adapter, ERROR,
			    "radar detection: scan already in process...\n");
		return -EBUSY;
	}

	if (!mwifiex_is_11h_active(priv)) {
		mwifiex_dbg(priv->adapter, INFO,
			    "Enable 11h extensions in FW\n");
		if (mwifiex_11h_activate(priv, true)) {
			mwifiex_dbg(priv->adapter, ERROR,
				    "Failed to activate 11h extensions!!");
			return -1;
		}
		priv->state_11h.is_11h_active = true;
	}

	memset(&radar_params, 0, sizeof(struct mwifiex_radar_params));
	radar_params.chandef = chandef;
	radar_params.cac_time_ms = cac_time_ms;

	memcpy(&priv->dfs_chandef, chandef, sizeof(priv->dfs_chandef));

	if (mwifiex_send_cmd(priv, HostCmd_CMD_CHAN_REPORT_REQUEST,
			     HostCmd_ACT_GEN_SET, 0, &radar_params, true))
		return -1;

	queue_delayed_work(priv->dfs_cac_workqueue, &priv->dfs_cac_work,
			   msecs_to_jiffies(cac_time_ms));
	return 0;
}