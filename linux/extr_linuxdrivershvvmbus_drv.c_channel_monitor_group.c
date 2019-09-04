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
typedef  int u8 ;
struct TYPE_2__ {scalar_t__ monitorid; } ;
struct vmbus_channel {TYPE_1__ offermsg; } ;

/* Variables and functions */

__attribute__((used)) static u8 channel_monitor_group(const struct vmbus_channel *channel)
{
	return (u8)channel->offermsg.monitorid / 32;
}