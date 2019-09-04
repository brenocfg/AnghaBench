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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  msgtype; } ;
struct vmbus_channel_relid_released {TYPE_1__ header; int /*<<< orphan*/  child_relid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNELMSG_RELID_RELEASED ; 
 int /*<<< orphan*/  memset (struct vmbus_channel_relid_released*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_vmbus_release_relid (struct vmbus_channel_relid_released*,int) ; 
 int vmbus_post_msg (struct vmbus_channel_relid_released*,int,int) ; 

__attribute__((used)) static void vmbus_release_relid(u32 relid)
{
	struct vmbus_channel_relid_released msg;
	int ret;

	memset(&msg, 0, sizeof(struct vmbus_channel_relid_released));
	msg.child_relid = relid;
	msg.header.msgtype = CHANNELMSG_RELID_RELEASED;
	ret = vmbus_post_msg(&msg, sizeof(struct vmbus_channel_relid_released),
			     true);

	trace_vmbus_release_relid(&msg, ret);
}