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
struct vmbus_channel {int /*<<< orphan*/  kobj; int /*<<< orphan*/  callback_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmbus_remove_channel_attr_group (struct vmbus_channel*) ; 

__attribute__((used)) static void free_channel(struct vmbus_channel *channel)
{
	tasklet_kill(&channel->callback_event);
	vmbus_remove_channel_attr_group(channel);

	kobject_put(&channel->kobj);
}