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
struct ieee80211_hw {struct ar9170* priv; } ;
struct ar9170 {int /*<<< orphan*/  mutex; int /*<<< orphan*/  beacon_iter; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR9170_MAC_REG_DMA_TRIGGER ; 
 int /*<<< orphan*/  CARL9170_IDLE ; 
 int /*<<< orphan*/  CARL9170_STARTED ; 
 scalar_t__ IS_ACCEPTING_CMD (struct ar9170*) ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  carl9170_cancel_worker (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_led_set_state (struct ar9170*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  carl9170_set_state_when (struct ar9170*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  carl9170_usb_stop (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_write_reg (struct ar9170*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  carl9170_zap_queues (struct ar9170*) ; 
 int /*<<< orphan*/  ieee80211_stop_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void carl9170_op_stop(struct ieee80211_hw *hw)
{
	struct ar9170 *ar = hw->priv;

	carl9170_set_state_when(ar, CARL9170_STARTED, CARL9170_IDLE);

	ieee80211_stop_queues(ar->hw);

	mutex_lock(&ar->mutex);
	if (IS_ACCEPTING_CMD(ar)) {
		RCU_INIT_POINTER(ar->beacon_iter, NULL);

		carl9170_led_set_state(ar, 0);

		/* stop DMA */
		carl9170_write_reg(ar, AR9170_MAC_REG_DMA_TRIGGER, 0);
		carl9170_usb_stop(ar);
	}

	carl9170_zap_queues(ar);
	mutex_unlock(&ar->mutex);

	carl9170_cancel_worker(ar);
}