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
struct hfi1_devdata {int /*<<< orphan*/  synth_stats_timer; int /*<<< orphan*/  update_cntr_work; int /*<<< orphan*/  update_cntr_wq; } ;

/* Variables and functions */
 int HZ ; 
 int SYNTH_CNT_TIME ; 
 struct hfi1_devdata* dd ; 
 struct hfi1_devdata* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synth_stats_timer ; 

__attribute__((used)) static void update_synth_timer(struct timer_list *t)
{
	struct hfi1_devdata *dd = from_timer(dd, t, synth_stats_timer);

	queue_work(dd->update_cntr_wq, &dd->update_cntr_work);
	mod_timer(&dd->synth_stats_timer, jiffies + HZ * SYNTH_CNT_TIME);
}