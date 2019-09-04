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
typedef  scalar_t__ u16 ;
struct ena_comp_ctx {int /*<<< orphan*/  wait_event; int /*<<< orphan*/  status; } ;
struct ena_com_admin_queue {scalar_t__ q_depth; int /*<<< orphan*/  comp_ctx; } ;
struct ena_com_dev {struct ena_com_admin_queue admin_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_CMD_ABORTED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct ena_comp_ctx* get_comp_ctxt (struct ena_com_admin_queue*,scalar_t__,int) ; 
 scalar_t__ unlikely (int) ; 

void ena_com_abort_admin_commands(struct ena_com_dev *ena_dev)
{
	struct ena_com_admin_queue *admin_queue = &ena_dev->admin_queue;
	struct ena_comp_ctx *comp_ctx;
	u16 i;

	if (!admin_queue->comp_ctx)
		return;

	for (i = 0; i < admin_queue->q_depth; i++) {
		comp_ctx = get_comp_ctxt(admin_queue, i, false);
		if (unlikely(!comp_ctx))
			break;

		comp_ctx->status = ENA_CMD_ABORTED;

		complete(&comp_ctx->wait_event);
	}
}