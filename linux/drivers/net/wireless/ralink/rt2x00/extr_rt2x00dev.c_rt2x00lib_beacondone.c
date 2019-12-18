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
struct rt2x00_dev {int /*<<< orphan*/  hw; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_STATE_ENABLED_RADIO ; 
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_RESUME_ALL ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rt2x00_dev*) ; 
 scalar_t__ rt2x00_has_cap_pre_tbtt_interrupt (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00lib_bc_buffer_iter ; 
 int /*<<< orphan*/  rt2x00lib_beaconupdate_iter ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rt2x00lib_beacondone(struct rt2x00_dev *rt2x00dev)
{
	if (!test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		return;

	/* send buffered bc/mc frames out for every bssid */
	ieee80211_iterate_active_interfaces_atomic(
		rt2x00dev->hw, IEEE80211_IFACE_ITER_RESUME_ALL,
		rt2x00lib_bc_buffer_iter, rt2x00dev);
	/*
	 * Devices with pre tbtt interrupt don't need to update the beacon
	 * here as they will fetch the next beacon directly prior to
	 * transmission.
	 */
	if (rt2x00_has_cap_pre_tbtt_interrupt(rt2x00dev))
		return;

	/* fetch next beacon */
	ieee80211_iterate_active_interfaces_atomic(
		rt2x00dev->hw, IEEE80211_IFACE_ITER_RESUME_ALL,
		rt2x00lib_beaconupdate_iter, rt2x00dev);
}