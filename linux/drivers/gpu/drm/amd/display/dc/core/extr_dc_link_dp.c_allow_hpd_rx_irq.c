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
struct TYPE_2__ {scalar_t__ lane_count; } ;
struct dc_link {scalar_t__ type; TYPE_1__ cur_link_settings; } ;

/* Variables and functions */
 scalar_t__ LANE_COUNT_UNKNOWN ; 
 scalar_t__ dc_connection_mst_branch ; 
 scalar_t__ is_dp_active_dongle (struct dc_link const*) ; 

__attribute__((used)) static bool allow_hpd_rx_irq(const struct dc_link *link)
{
	/*
	 * Don't handle RX IRQ unless one of following is met:
	 * 1) The link is established (cur_link_settings != unknown)
	 * 2) We kicked off MST detection
	 * 3) We know we're dealing with an active dongle
	 */

	if ((link->cur_link_settings.lane_count != LANE_COUNT_UNKNOWN) ||
		(link->type == dc_connection_mst_branch) ||
		is_dp_active_dongle(link))
		return true;

	return false;
}