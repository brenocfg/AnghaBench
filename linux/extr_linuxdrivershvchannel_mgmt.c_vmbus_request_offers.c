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
struct vmbus_channel_msginfo {scalar_t__ msg; } ;
struct vmbus_channel_message_header {int /*<<< orphan*/  msgtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNELMSG_REQUESTOFFERS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct vmbus_channel_msginfo*) ; 
 struct vmbus_channel_msginfo* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  trace_vmbus_request_offers (int) ; 
 int vmbus_post_msg (struct vmbus_channel_message_header*,int,int) ; 

int vmbus_request_offers(void)
{
	struct vmbus_channel_message_header *msg;
	struct vmbus_channel_msginfo *msginfo;
	int ret;

	msginfo = kmalloc(sizeof(*msginfo) +
			  sizeof(struct vmbus_channel_message_header),
			  GFP_KERNEL);
	if (!msginfo)
		return -ENOMEM;

	msg = (struct vmbus_channel_message_header *)msginfo->msg;

	msg->msgtype = CHANNELMSG_REQUESTOFFERS;

	ret = vmbus_post_msg(msg, sizeof(struct vmbus_channel_message_header),
			     true);

	trace_vmbus_request_offers(ret);

	if (ret != 0) {
		pr_err("Unable to request offers - %d\n", ret);

		goto cleanup;
	}

cleanup:
	kfree(msginfo);

	return ret;
}