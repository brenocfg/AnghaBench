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
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_2__ {unsigned long long beacon_int; int /*<<< orphan*/  dev; } ;
struct mt76x02_dev {int /*<<< orphan*/  pre_tbtt_timer; TYPE_1__ mt76; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  MT_TBTT_TIMER ; 
 int /*<<< orphan*/  MT_TBTT_TIMER_VAL ; 
 int /*<<< orphan*/  MT_TSF_TIMER_DW0 ; 
 int /*<<< orphan*/  MT_TSF_TIMER_DW1 ; 
 int PRE_TBTT_USEC ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int mt76_get_field (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mt76_rr (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mt76x02u_restart_pre_tbtt_timer(struct mt76x02_dev *dev)
{
	u32 tbtt, dw0, dw1;
	u64 tsf, time;

	/* Get remaining TBTT in usec */
	tbtt = mt76_get_field(dev, MT_TBTT_TIMER, MT_TBTT_TIMER_VAL);
	tbtt *= 32;

	dw0 = mt76_rr(dev, MT_TSF_TIMER_DW0);
	dw1 = mt76_rr(dev, MT_TSF_TIMER_DW1);
	tsf = (u64)dw0 << 32 | dw1;
	dev_dbg(dev->mt76.dev, "TSF: %llu us TBTT %u us\n", tsf, tbtt);

	/* Convert beacon interval in TU (1024 usec) to nsec */
	time = ((1000000000ull * dev->mt76.beacon_int) >> 10);

	/* Adjust time to trigger hrtimer 8ms before TBTT */
	if (tbtt < PRE_TBTT_USEC)
		time -= (PRE_TBTT_USEC - tbtt) * 1000ull;
	else
		time += (tbtt - PRE_TBTT_USEC) * 1000ull;

	hrtimer_start(&dev->pre_tbtt_timer, time, HRTIMER_MODE_REL);
}