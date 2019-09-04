#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  child_relid; } ;
struct vmbus_channel {TYPE_1__ offermsg; } ;
struct hv_device {struct vmbus_channel* channel; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  channel_mutex; } ;

/* Variables and functions */
 struct hv_device* device_to_hv_device (struct device*) ; 
 int /*<<< orphan*/  hv_process_channel_removal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct hv_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__ vmbus_connection ; 

__attribute__((used)) static void vmbus_device_release(struct device *device)
{
	struct hv_device *hv_dev = device_to_hv_device(device);
	struct vmbus_channel *channel = hv_dev->channel;

	mutex_lock(&vmbus_connection.channel_mutex);
	hv_process_channel_removal(channel->offermsg.child_relid);
	mutex_unlock(&vmbus_connection.channel_mutex);
	kfree(hv_dev);

}