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
struct rsi_hw {struct rsi_common* priv; TYPE_1__* host_intf_ops; } ;
struct rsi_common {int reinit_hw; int iface_down; int /*<<< orphan*/  mutex; int /*<<< orphan*/  wlan_init_completion; scalar_t__ hibernate_resume; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; struct rsi_hw* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reinit_device ) (struct rsi_hw*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_ZONE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsi_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rsi_send_rx_filter_frame (struct rsi_common*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct rsi_hw*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiphy_rfkill_start_polling (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rsi_mac80211_start(struct ieee80211_hw *hw)
{
	struct rsi_hw *adapter = hw->priv;
	struct rsi_common *common = adapter->priv;

	rsi_dbg(ERR_ZONE, "===> Interface UP <===\n");
	mutex_lock(&common->mutex);
	if (common->hibernate_resume) {
		common->reinit_hw = true;
		adapter->host_intf_ops->reinit_device(adapter);
		wait_for_completion(&adapter->priv->wlan_init_completion);
	}
	common->iface_down = false;
	wiphy_rfkill_start_polling(hw->wiphy);
	rsi_send_rx_filter_frame(common, 0);
	mutex_unlock(&common->mutex);

	return 0;
}