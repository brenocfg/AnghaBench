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
struct TYPE_5__ {size_t node; } ;
struct TYPE_4__ {int /*<<< orphan*/  node; } ;
struct scifmsg {size_t* payload; TYPE_2__ dst; TYPE_1__ src; int /*<<< orphan*/  uop; } ;
struct scif_dev {int node_remove_ack_pending; size_t node; int exit_ack_pending; } ;
struct TYPE_6__ {int /*<<< orphan*/  nodeid; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_EXIT_ACK ; 
 size_t SCIF_MGMT_NODE ; 
 int /*<<< orphan*/  SCIF_NODE_REMOVE_ACK ; 
 struct scif_dev* scif_dev ; 
 TYPE_3__ scif_info ; 
 int /*<<< orphan*/  scif_nodeqp_send (struct scif_dev*,struct scifmsg*) ; 

void scif_send_acks(struct scif_dev *dev)
{
	struct scifmsg msg;

	if (dev->node_remove_ack_pending) {
		msg.uop = SCIF_NODE_REMOVE_ACK;
		msg.src.node = scif_info.nodeid;
		msg.dst.node = SCIF_MGMT_NODE;
		msg.payload[0] = dev->node;
		scif_nodeqp_send(&scif_dev[SCIF_MGMT_NODE], &msg);
		dev->node_remove_ack_pending = false;
	}
	if (dev->exit_ack_pending) {
		msg.uop = SCIF_EXIT_ACK;
		msg.src.node = scif_info.nodeid;
		msg.dst.node = dev->node;
		scif_nodeqp_send(dev, &msg);
		dev->exit_ack_pending = false;
	}
}