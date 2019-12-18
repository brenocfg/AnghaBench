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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct vmbus_channel {int dummy; } ;
struct hv_monitor_page {TYPE_1__* trigger_group; } ;
struct TYPE_2__ {int /*<<< orphan*/  pending; } ;

/* Variables and functions */
 size_t channel_monitor_group (struct vmbus_channel const*) ; 

__attribute__((used)) static u32 channel_pending(const struct vmbus_channel *channel,
			   const struct hv_monitor_page *monitor_page)
{
	u8 monitor_group = channel_monitor_group(channel);

	return monitor_page->trigger_group[monitor_group].pending;
}