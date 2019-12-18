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
struct igb_adapter {int dummy; } ;

/* Variables and functions */
 int IGB_MAC_STATE_QUEUE_STEERING ; 
 int igb_del_mac_filter_flags (struct igb_adapter*,int const*,int,int) ; 

int igb_del_mac_steering_filter(struct igb_adapter *adapter,
				const u8 *addr, u8 queue, u8 flags)
{
	return igb_del_mac_filter_flags(adapter, addr, queue,
					IGB_MAC_STATE_QUEUE_STEERING | flags);
}