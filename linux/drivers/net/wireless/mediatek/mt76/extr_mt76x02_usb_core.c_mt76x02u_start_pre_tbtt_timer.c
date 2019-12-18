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
typedef  int u64 ;
typedef  int u32 ;
struct mt76x02_dev {int /*<<< orphan*/  pre_tbtt_timer; int /*<<< orphan*/  pre_tbtt_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  MT_TBTT_TIMER ; 
 int /*<<< orphan*/  MT_TBTT_TIMER_VAL ; 
 int PRE_TBTT_USEC ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int mt76_get_field (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_highpri_wq ; 

__attribute__((used)) static void mt76x02u_start_pre_tbtt_timer(struct mt76x02_dev *dev)
{
	u64 time;
	u32 tbtt;

	/* Get remaining TBTT in usec */
	tbtt = mt76_get_field(dev, MT_TBTT_TIMER, MT_TBTT_TIMER_VAL);
	tbtt *= 32;

	if (tbtt <= PRE_TBTT_USEC) {
		queue_work(system_highpri_wq, &dev->pre_tbtt_work);
		return;
	}

	time = (tbtt - PRE_TBTT_USEC) * 1000ull;
	hrtimer_start(&dev->pre_tbtt_timer, time, HRTIMER_MODE_REL);
}