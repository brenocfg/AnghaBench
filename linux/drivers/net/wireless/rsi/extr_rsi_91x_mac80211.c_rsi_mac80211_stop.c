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
struct rsi_common {int iface_down; int /*<<< orphan*/  mutex; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; struct rsi_hw* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_ZONE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsi_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rsi_send_rx_filter_frame (struct rsi_common*,int) ; 
 int /*<<< orphan*/  wiphy_rfkill_stop_polling (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rsi_mac80211_stop(struct ieee80211_hw *hw)
{
	struct rsi_hw *adapter = hw->priv;
	struct rsi_common *common = adapter->priv;

	rsi_dbg(ERR_ZONE, "===> Interface DOWN <===\n");
	mutex_lock(&common->mutex);
	common->iface_down = true;
	wiphy_rfkill_stop_polling(hw->wiphy);

	/* Block all rx frames */
	rsi_send_rx_filter_frame(common, 0xffff);

	mutex_unlock(&common->mutex);
}