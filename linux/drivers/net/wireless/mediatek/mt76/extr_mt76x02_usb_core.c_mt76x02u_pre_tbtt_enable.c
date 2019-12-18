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
struct TYPE_2__ {scalar_t__ beacon_mask; } ;
struct mt76x02_dev {int /*<<< orphan*/  pre_tbtt_timer; TYPE_1__ mt76; } ;

/* Variables and functions */
 int /*<<< orphan*/  hrtimer_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76x02u_start_pre_tbtt_timer (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x02u_stop_pre_tbtt_timer (struct mt76x02_dev*) ; 

__attribute__((used)) static void mt76x02u_pre_tbtt_enable(struct mt76x02_dev *dev, bool en)
{
	if (en && dev->mt76.beacon_mask &&
	    !hrtimer_active(&dev->pre_tbtt_timer))
		mt76x02u_start_pre_tbtt_timer(dev);
	if (!en)
		mt76x02u_stop_pre_tbtt_timer(dev);
}