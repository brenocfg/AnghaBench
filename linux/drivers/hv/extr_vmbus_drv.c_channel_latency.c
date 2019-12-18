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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct vmbus_channel {int dummy; } ;
struct hv_monitor_page {int /*<<< orphan*/ ** latency; } ;

/* Variables and functions */
 size_t channel_monitor_group (struct vmbus_channel const*) ; 
 size_t channel_monitor_offset (struct vmbus_channel const*) ; 

__attribute__((used)) static u32 channel_latency(const struct vmbus_channel *channel,
			   const struct hv_monitor_page *monitor_page)
{
	u8 monitor_group = channel_monitor_group(channel);
	u8 monitor_offset = channel_monitor_offset(channel);

	return monitor_page->latency[monitor_group][monitor_offset];
}