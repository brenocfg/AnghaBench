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
typedef  int /*<<< orphan*/  u8 ;
struct ieee80211_hw {struct ath9k_htc_priv* priv; } ;
struct ath_hw {scalar_t__ is_monitoring; } ;
struct ath_common {int /*<<< orphan*/  op_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  cleanup_timer; } ;
struct ath9k_htc_priv {int /*<<< orphan*/  mutex; struct ath_hw* ah; int /*<<< orphan*/  led_work; int /*<<< orphan*/  ps_work; int /*<<< orphan*/  fatal_work; TYPE_1__ tx; int /*<<< orphan*/  rx_tasklet; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANY ; 
 int /*<<< orphan*/  ATH9K_PM_FULL_SLEEP ; 
 int /*<<< orphan*/  ATH_OP_INVALID ; 
 int /*<<< orphan*/  CONFIG ; 
 int /*<<< orphan*/  WMI_CMD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WMI_DISABLE_INTR_CMDID ; 
 int /*<<< orphan*/  WMI_DRAIN_TXQ_ALL_CMDID ; 
 int /*<<< orphan*/  WMI_STOP_RECV_CMDID ; 
 int /*<<< orphan*/  ath9k_htc_ps_restore (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_htc_ps_wakeup (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_htc_remove_monitor_interface (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_htc_setpower (struct ath9k_htc_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_htc_stop_ani (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_htc_stop_btcoex (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_htc_tx_drain (struct ath9k_htc_priv*) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_disable (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_phy_disable (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_wmi_event_drain (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath9k_htc_stop(struct ieee80211_hw *hw)
{
	struct ath9k_htc_priv *priv = hw->priv;
	struct ath_hw *ah = priv->ah;
	struct ath_common *common = ath9k_hw_common(ah);
	int ret __attribute__ ((unused));
	u8 cmd_rsp;

	mutex_lock(&priv->mutex);

	if (test_bit(ATH_OP_INVALID, &common->op_flags)) {
		ath_dbg(common, ANY, "Device not present\n");
		mutex_unlock(&priv->mutex);
		return;
	}

	ath9k_htc_ps_wakeup(priv);

	WMI_CMD(WMI_DISABLE_INTR_CMDID);
	WMI_CMD(WMI_DRAIN_TXQ_ALL_CMDID);
	WMI_CMD(WMI_STOP_RECV_CMDID);

	tasklet_kill(&priv->rx_tasklet);

	del_timer_sync(&priv->tx.cleanup_timer);
	ath9k_htc_tx_drain(priv);
	ath9k_wmi_event_drain(priv);

	mutex_unlock(&priv->mutex);

	/* Cancel all the running timers/work .. */
	cancel_work_sync(&priv->fatal_work);
	cancel_work_sync(&priv->ps_work);

#ifdef CONFIG_MAC80211_LEDS
	cancel_work_sync(&priv->led_work);
#endif
	ath9k_htc_stop_ani(priv);

	mutex_lock(&priv->mutex);

	ath9k_htc_stop_btcoex(priv);

	/* Remove a monitor interface if it's present. */
	if (priv->ah->is_monitoring)
		ath9k_htc_remove_monitor_interface(priv);

	ath9k_hw_phy_disable(ah);
	ath9k_hw_disable(ah);
	ath9k_htc_ps_restore(priv);
	ath9k_htc_setpower(priv, ATH9K_PM_FULL_SLEEP);

	set_bit(ATH_OP_INVALID, &common->op_flags);

	ath_dbg(common, CONFIG, "Driver halt\n");
	mutex_unlock(&priv->mutex);
}