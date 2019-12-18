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
struct vmbus_channel {int dummy; } ;

/* Variables and functions */
 scalar_t__ vmbus_disconnect_ring (struct vmbus_channel*) ; 
 int /*<<< orphan*/  vmbus_free_ring (struct vmbus_channel*) ; 

void vmbus_close(struct vmbus_channel *channel)
{
	if (vmbus_disconnect_ring(channel) == 0)
		vmbus_free_ring(channel);
}