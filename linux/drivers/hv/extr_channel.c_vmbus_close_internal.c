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
struct TYPE_5__ {int /*<<< orphan*/  msgtype; } ;
struct vmbus_channel_close_channel {int /*<<< orphan*/  child_relid; TYPE_2__ header; } ;
struct TYPE_6__ {int /*<<< orphan*/  child_relid; } ;
struct TYPE_4__ {struct vmbus_channel_close_channel msg; } ;
struct vmbus_channel {scalar_t__ state; scalar_t__ ringbuffer_gpadlhandle; TYPE_3__ offermsg; TYPE_1__ close_msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNELMSG_CLOSECHANNEL ; 
 scalar_t__ CHANNEL_OPENED_STATE ; 
 scalar_t__ CHANNEL_OPEN_STATE ; 
 int EINVAL ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  trace_vmbus_close_internal (struct vmbus_channel_close_channel*,int) ; 
 int vmbus_post_msg (struct vmbus_channel_close_channel*,int,int) ; 
 int /*<<< orphan*/  vmbus_reset_channel_cb (struct vmbus_channel*) ; 
 int vmbus_teardown_gpadl (struct vmbus_channel*,scalar_t__) ; 

__attribute__((used)) static int vmbus_close_internal(struct vmbus_channel *channel)
{
	struct vmbus_channel_close_channel *msg;
	int ret;

	vmbus_reset_channel_cb(channel);

	/*
	 * In case a device driver's probe() fails (e.g.,
	 * util_probe() -> vmbus_open() returns -ENOMEM) and the device is
	 * rescinded later (e.g., we dynamically disable an Integrated Service
	 * in Hyper-V Manager), the driver's remove() invokes vmbus_close():
	 * here we should skip most of the below cleanup work.
	 */
	if (channel->state != CHANNEL_OPENED_STATE)
		return -EINVAL;

	channel->state = CHANNEL_OPEN_STATE;

	/* Send a closing message */

	msg = &channel->close_msg.msg;

	msg->header.msgtype = CHANNELMSG_CLOSECHANNEL;
	msg->child_relid = channel->offermsg.child_relid;

	ret = vmbus_post_msg(msg, sizeof(struct vmbus_channel_close_channel),
			     true);

	trace_vmbus_close_internal(msg, ret);

	if (ret) {
		pr_err("Close failed: close post msg return is %d\n", ret);
		/*
		 * If we failed to post the close msg,
		 * it is perhaps better to leak memory.
		 */
	}

	/* Tear down the gpadl for the channel's ring buffer */
	else if (channel->ringbuffer_gpadlhandle) {
		ret = vmbus_teardown_gpadl(channel,
					   channel->ringbuffer_gpadlhandle);
		if (ret) {
			pr_err("Close failed: teardown gpadl return %d\n", ret);
			/*
			 * If we failed to teardown gpadl,
			 * it is perhaps better to leak memory.
			 */
		}

		channel->ringbuffer_gpadlhandle = 0;
	}

	return ret;
}