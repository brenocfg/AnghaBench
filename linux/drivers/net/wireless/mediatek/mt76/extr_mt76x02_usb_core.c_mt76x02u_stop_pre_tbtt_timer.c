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
struct mt76x02_dev {int /*<<< orphan*/  pre_tbtt_work; int /*<<< orphan*/  pre_tbtt_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ hrtimer_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mt76x02u_stop_pre_tbtt_timer(struct mt76x02_dev *dev)
{
	do {
		hrtimer_cancel(&dev->pre_tbtt_timer);
		cancel_work_sync(&dev->pre_tbtt_work);
		/* Timer can be rearmed by work. */
	} while (hrtimer_active(&dev->pre_tbtt_timer));
}