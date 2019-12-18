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
struct ieee80211_hw {struct ar5523* priv; } ;
struct ar5523 {int /*<<< orphan*/  mutex; int /*<<< orphan*/  rx_refill_work; int /*<<< orphan*/  tx_wd_work; int /*<<< orphan*/  tx_wd_timer; int /*<<< orphan*/  flags; int /*<<< orphan*/  stat_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR5523_HW_UP ; 
 int /*<<< orphan*/  UATH_LED_ACTIVITY ; 
 int /*<<< orphan*/  UATH_LED_LINK ; 
 int /*<<< orphan*/  UATH_LED_OFF ; 
 int /*<<< orphan*/  WDCMSG_TARGET_STOP ; 
 int /*<<< orphan*/  ar5523_cancel_rx_bufs (struct ar5523*) ; 
 int /*<<< orphan*/  ar5523_cmd_write (struct ar5523*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar5523_dbg (struct ar5523*,char*) ; 
 int /*<<< orphan*/  ar5523_set_ledsteady (struct ar5523*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ar5523_stop(struct ieee80211_hw *hw)
{
	struct ar5523 *ar = hw->priv;

	ar5523_dbg(ar, "stop called\n");

	cancel_delayed_work_sync(&ar->stat_work);
	mutex_lock(&ar->mutex);
	clear_bit(AR5523_HW_UP, &ar->flags);

	ar5523_set_ledsteady(ar, UATH_LED_LINK, UATH_LED_OFF);
	ar5523_set_ledsteady(ar, UATH_LED_ACTIVITY, UATH_LED_OFF);

	ar5523_cmd_write(ar, WDCMSG_TARGET_STOP, NULL, 0, 0);

	del_timer_sync(&ar->tx_wd_timer);
	cancel_work_sync(&ar->tx_wd_work);
	cancel_work_sync(&ar->rx_refill_work);
	ar5523_cancel_rx_bufs(ar);
	mutex_unlock(&ar->mutex);
}