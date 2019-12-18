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
struct TYPE_2__ {int inited; int /*<<< orphan*/  tx_aborted; int /*<<< orphan*/  tx_multi_collision; int /*<<< orphan*/  tx_errors; } ;
struct rtl8169_private {TYPE_1__ tc_offset; struct rtl8169_counters* counters; } ;
struct rtl8169_counters {int /*<<< orphan*/  tx_aborted; int /*<<< orphan*/  tx_multi_collision; int /*<<< orphan*/  tx_errors; } ;

/* Variables and functions */
 scalar_t__ rtl8169_reset_counters (struct rtl8169_private*) ; 
 scalar_t__ rtl8169_update_counters (struct rtl8169_private*) ; 

__attribute__((used)) static bool rtl8169_init_counter_offsets(struct rtl8169_private *tp)
{
	struct rtl8169_counters *counters = tp->counters;
	bool ret = false;

	/*
	 * rtl8169_init_counter_offsets is called from rtl_open.  On chip
	 * versions prior to RTL_GIGA_MAC_VER_19 the tally counters are only
	 * reset by a power cycle, while the counter values collected by the
	 * driver are reset at every driver unload/load cycle.
	 *
	 * To make sure the HW values returned by @get_stats64 match the SW
	 * values, we collect the initial values at first open(*) and use them
	 * as offsets to normalize the values returned by @get_stats64.
	 *
	 * (*) We can't call rtl8169_init_counter_offsets from rtl_init_one
	 * for the reason stated in rtl8169_update_counters; CmdRxEnb is only
	 * set at open time by rtl_hw_start.
	 */

	if (tp->tc_offset.inited)
		return true;

	/* If both, reset and update fail, propagate to caller. */
	if (rtl8169_reset_counters(tp))
		ret = true;

	if (rtl8169_update_counters(tp))
		ret = true;

	tp->tc_offset.tx_errors = counters->tx_errors;
	tp->tc_offset.tx_multi_collision = counters->tx_multi_collision;
	tp->tc_offset.tx_aborted = counters->tx_aborted;
	tp->tc_offset.inited = true;

	return ret;
}