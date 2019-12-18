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
typedef  int u32 ;
struct TYPE_2__ {int beacon_int; } ;
struct mt76x02_dev {int tbtt_count; TYPE_1__ mt76; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_BEACON_TIME_CFG ; 
 int /*<<< orphan*/  MT_BEACON_TIME_CFG_INTVAL ; 
 int /*<<< orphan*/  mt76_rmw_field (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
mt76x02_resync_beacon_timer(struct mt76x02_dev *dev)
{
	u32 timer_val = dev->mt76.beacon_int << 4;

	dev->tbtt_count++;

	/*
	 * Beacon timer drifts by 1us every tick, the timer is configured
	 * in 1/16 TU (64us) units.
	 */
	if (dev->tbtt_count < 63)
		return;

	/*
	 * The updated beacon interval takes effect after two TBTT, because
	 * at this point the original interval has already been loaded into
	 * the next TBTT_TIMER value
	 */
	if (dev->tbtt_count == 63)
		timer_val -= 1;

	mt76_rmw_field(dev, MT_BEACON_TIME_CFG,
		       MT_BEACON_TIME_CFG_INTVAL, timer_val);

	if (dev->tbtt_count >= 64)
		dev->tbtt_count = 0;
}