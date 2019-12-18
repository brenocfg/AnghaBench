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
typedef  int u8 ;
struct igc_adapter {int dummy; } ;

/* Variables and functions */
 int IGC_MAC_STATE_QUEUE_STEERING ; 
 int igc_add_mac_filter_flags (struct igc_adapter*,int const*,int,int) ; 

int igc_add_mac_steering_filter(struct igc_adapter *adapter,
				const u8 *addr, u8 queue, u8 flags)
{
	return igc_add_mac_filter_flags(adapter, addr, queue,
					IGC_MAC_STATE_QUEUE_STEERING | flags);
}