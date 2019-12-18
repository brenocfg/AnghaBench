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
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00_dev {int dummy; } ;
struct queue_entry {int /*<<< orphan*/  flags; int /*<<< orphan*/  entry_idx; TYPE_1__* queue; } ;
struct TYPE_2__ {struct rt2x00_dev* rt2x00dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCN_TIME_CFG ; 
 int /*<<< orphan*/  BCN_TIME_CFG_BEACON_GEN ; 
 int /*<<< orphan*/  ENTRY_BCN_ENABLED ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2800_clear_beacon_register (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2800_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2800_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2800_update_beacons_setup (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rt2800_clear_beacon(struct queue_entry *entry)
{
	struct rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;
	u32 orig_reg, reg;

	/*
	 * Disable beaconing while we are reloading the beacon data,
	 * otherwise we might be sending out invalid data.
	 */
	orig_reg = rt2800_register_read(rt2x00dev, BCN_TIME_CFG);
	reg = orig_reg;
	rt2x00_set_field32(&reg, BCN_TIME_CFG_BEACON_GEN, 0);
	rt2800_register_write(rt2x00dev, BCN_TIME_CFG, reg);

	/*
	 * Clear beacon.
	 */
	rt2800_clear_beacon_register(rt2x00dev, entry->entry_idx);
	__clear_bit(ENTRY_BCN_ENABLED, &entry->flags);

	/*
	 * Change global beacons settings.
	 */
	rt2800_update_beacons_setup(rt2x00dev);
	/*
	 * Restore beaconing state.
	 */
	rt2800_register_write(rt2x00dev, BCN_TIME_CFG, orig_reg);
}