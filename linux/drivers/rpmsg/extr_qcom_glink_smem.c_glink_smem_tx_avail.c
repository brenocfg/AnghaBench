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
typedef  scalar_t__ u32 ;
struct qcom_glink_pipe {int dummy; } ;
struct TYPE_2__ {scalar_t__ length; } ;
struct glink_smem_pipe {TYPE_1__ native; int /*<<< orphan*/ * tail; int /*<<< orphan*/ * head; } ;

/* Variables and functions */
 scalar_t__ FIFO_FULL_RESERVE ; 
 scalar_t__ TX_BLOCKED_CMD_RESERVE ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct glink_smem_pipe* to_smem_pipe (struct qcom_glink_pipe*) ; 

__attribute__((used)) static size_t glink_smem_tx_avail(struct qcom_glink_pipe *np)
{
	struct glink_smem_pipe *pipe = to_smem_pipe(np);
	u32 head;
	u32 tail;
	u32 avail;

	head = le32_to_cpu(*pipe->head);
	tail = le32_to_cpu(*pipe->tail);

	if (tail <= head)
		avail = pipe->native.length - head + tail;
	else
		avail = tail - head;

	if (avail < (FIFO_FULL_RESERVE + TX_BLOCKED_CMD_RESERVE))
		avail = 0;
	else
		avail -= FIFO_FULL_RESERVE + TX_BLOCKED_CMD_RESERVE;

	return avail;
}