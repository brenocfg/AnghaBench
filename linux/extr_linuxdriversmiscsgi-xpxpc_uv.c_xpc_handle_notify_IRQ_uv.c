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
struct xpc_partition {int dummy; } ;
struct TYPE_3__ {short partid; } ;
struct xpc_notify_mq_msg_uv {TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  gru_mq_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 short XP_MAX_NPARTITIONS_UV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,short) ; 
 int /*<<< orphan*/  gru_free_message (int /*<<< orphan*/ ,struct xpc_notify_mq_msg_uv*) ; 
 struct xpc_notify_mq_msg_uv* gru_get_next_message (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpc_handle_notify_mq_msg_uv (struct xpc_partition*,struct xpc_notify_mq_msg_uv*) ; 
 TYPE_2__* xpc_notify_mq_uv ; 
 int /*<<< orphan*/  xpc_part ; 
 int /*<<< orphan*/  xpc_part_deref (struct xpc_partition*) ; 
 scalar_t__ xpc_part_ref (struct xpc_partition*) ; 
 struct xpc_partition* xpc_partitions ; 

__attribute__((used)) static irqreturn_t
xpc_handle_notify_IRQ_uv(int irq, void *dev_id)
{
	struct xpc_notify_mq_msg_uv *msg;
	short partid;
	struct xpc_partition *part;

	while ((msg = gru_get_next_message(xpc_notify_mq_uv->gru_mq_desc)) !=
	       NULL) {

		partid = msg->hdr.partid;
		if (partid < 0 || partid >= XP_MAX_NPARTITIONS_UV) {
			dev_err(xpc_part, "xpc_handle_notify_IRQ_uv() received "
				"invalid partid=0x%x in message\n", partid);
		} else {
			part = &xpc_partitions[partid];

			if (xpc_part_ref(part)) {
				xpc_handle_notify_mq_msg_uv(part, msg);
				xpc_part_deref(part);
			}
		}

		gru_free_message(xpc_notify_mq_uv->gru_mq_desc, msg);
	}

	return IRQ_HANDLED;
}