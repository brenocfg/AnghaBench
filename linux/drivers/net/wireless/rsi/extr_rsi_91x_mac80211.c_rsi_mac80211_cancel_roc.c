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
struct rsi_hw {struct rsi_common* priv; } ;
struct rsi_common {int /*<<< orphan*/  mutex; int /*<<< orphan*/  roc_timer; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct rsi_hw* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFO_ZONE ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsi_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rsi_resume_conn_channel (struct rsi_common*) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rsi_mac80211_cancel_roc(struct ieee80211_hw *hw,
				   struct ieee80211_vif *vif)
{
	struct rsi_hw *adapter = hw->priv;
	struct rsi_common *common = adapter->priv;

	rsi_dbg(INFO_ZONE, "Cancel remain on channel\n");

	mutex_lock(&common->mutex);
	if (!timer_pending(&common->roc_timer)) {
		mutex_unlock(&common->mutex);
		return 0;
	}

	del_timer(&common->roc_timer);

	rsi_resume_conn_channel(common);
	mutex_unlock(&common->mutex);

	return 0;
}