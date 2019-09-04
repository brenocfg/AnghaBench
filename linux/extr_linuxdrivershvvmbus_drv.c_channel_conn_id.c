#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct vmbus_channel {int dummy; } ;
struct hv_monitor_page {TYPE_3__** parameter; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {TYPE_1__ u; } ;
struct TYPE_6__ {TYPE_2__ connectionid; } ;

/* Variables and functions */
 size_t channel_monitor_group (struct vmbus_channel*) ; 
 size_t channel_monitor_offset (struct vmbus_channel*) ; 

__attribute__((used)) static u32 channel_conn_id(struct vmbus_channel *channel,
			   struct hv_monitor_page *monitor_page)
{
	u8 monitor_group = channel_monitor_group(channel);
	u8 monitor_offset = channel_monitor_offset(channel);
	return monitor_page->parameter[monitor_group][monitor_offset].connectionid.u.id;
}