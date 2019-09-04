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
struct TYPE_5__ {int /*<<< orphan*/  node; } ;
struct TYPE_4__ {int /*<<< orphan*/  node; } ;
struct scifmsg {TYPE_2__ dst; TYPE_1__ src; int /*<<< orphan*/  uop; } ;
struct scif_dev {scalar_t__ exit; int /*<<< orphan*/  node; } ;
struct TYPE_6__ {int /*<<< orphan*/  exitwq; int /*<<< orphan*/  nodeid; } ;

/* Variables and functions */
 scalar_t__ OP_COMPLETED ; 
 scalar_t__ OP_IDLE ; 
 scalar_t__ OP_IN_PROGRESS ; 
 int /*<<< orphan*/  SCIF_EXIT ; 
 int /*<<< orphan*/  SCIF_NODE_ALIVE_TIMEOUT ; 
 TYPE_3__ scif_info ; 
 int scif_nodeqp_send (struct scif_dev*,struct scifmsg*) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void scif_send_exit(struct scif_dev *scifdev)
{
	struct scifmsg msg;
	int ret;

	scifdev->exit = OP_IN_PROGRESS;
	msg.uop = SCIF_EXIT;
	msg.src.node = scif_info.nodeid;
	msg.dst.node = scifdev->node;
	ret = scif_nodeqp_send(scifdev, &msg);
	if (ret)
		goto done;
	/* Wait for a SCIF_EXIT_ACK message */
	wait_event_timeout(scif_info.exitwq, scifdev->exit == OP_COMPLETED,
			   SCIF_NODE_ALIVE_TIMEOUT);
done:
	scifdev->exit = OP_IDLE;
}