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
struct timer_list {int dummy; } ;
struct ar5523 {int /*<<< orphan*/  tx_wd_work; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 struct ar5523* ar ; 
 int /*<<< orphan*/  ar5523_dbg (struct ar5523*,char*) ; 
 struct ar5523* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx_wd_timer ; 

__attribute__((used)) static void ar5523_tx_wd_timer(struct timer_list *t)
{
	struct ar5523 *ar = from_timer(ar, t, tx_wd_timer);

	ar5523_dbg(ar, "TX watchdog timer triggered\n");
	ieee80211_queue_work(ar->hw, &ar->tx_wd_work);
}