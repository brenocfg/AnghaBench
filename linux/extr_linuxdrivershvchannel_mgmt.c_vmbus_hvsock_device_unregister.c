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
struct vmbus_channel {int /*<<< orphan*/  device_obj; int /*<<< orphan*/  rescind; int /*<<< orphan*/  probe_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_hvsock_channel (struct vmbus_channel*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  vmbus_device_unregister (int /*<<< orphan*/ ) ; 

void vmbus_hvsock_device_unregister(struct vmbus_channel *channel)
{
	BUG_ON(!is_hvsock_channel(channel));

	/* We always get a rescind msg when a connection is closed. */
	while (!READ_ONCE(channel->probe_done) || !READ_ONCE(channel->rescind))
		msleep(1);

	vmbus_device_unregister(channel->device_obj);
}