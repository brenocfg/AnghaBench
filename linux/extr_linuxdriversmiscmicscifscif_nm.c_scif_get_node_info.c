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
typedef  scalar_t__ u64 ;
struct TYPE_5__ {size_t node; } ;
struct TYPE_4__ {int /*<<< orphan*/  node; } ;
struct scifmsg {scalar_t__* payload; TYPE_2__ dst; TYPE_1__ src; int /*<<< orphan*/  uop; } ;
struct TYPE_6__ {int /*<<< orphan*/  nodeid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIF_GET_NODE_INFO ; 
 size_t SCIF_MGMT_NODE ; 
 int /*<<< orphan*/  node_info ; 
 int /*<<< orphan*/ * scif_dev ; 
 TYPE_3__ scif_info ; 
 scalar_t__ scif_nodeqp_send (int /*<<< orphan*/ *,struct scifmsg*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void scif_get_node_info(void)
{
	struct scifmsg msg;
	DECLARE_COMPLETION_ONSTACK(node_info);

	msg.uop = SCIF_GET_NODE_INFO;
	msg.src.node = scif_info.nodeid;
	msg.dst.node = SCIF_MGMT_NODE;
	msg.payload[3] = (u64)&node_info;

	if ((scif_nodeqp_send(&scif_dev[SCIF_MGMT_NODE], &msg)))
		return;

	/* Wait for a response with SCIF_GET_NODE_INFO */
	wait_for_completion(&node_info);
}