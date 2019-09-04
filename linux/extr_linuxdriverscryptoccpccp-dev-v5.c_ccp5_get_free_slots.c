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
typedef  int u32 ;
struct ccp_cmd_queue {unsigned int qidx; int /*<<< orphan*/  reg_head_lo; int /*<<< orphan*/  qdma_tail; } ;
struct ccp5_desc {int dummy; } ;

/* Variables and functions */
 unsigned int COMMANDS_PER_QUEUE ; 
 int ioread32 (int /*<<< orphan*/ ) ; 
 int low_address (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int ccp5_get_free_slots(struct ccp_cmd_queue *cmd_q)
{
	unsigned int head_idx, n;
	u32 head_lo, queue_start;

	queue_start = low_address(cmd_q->qdma_tail);
	head_lo = ioread32(cmd_q->reg_head_lo);
	head_idx = (head_lo - queue_start) / sizeof(struct ccp5_desc);

	n = head_idx + COMMANDS_PER_QUEUE - cmd_q->qidx - 1;

	return n % COMMANDS_PER_QUEUE; /* Always one unused spot */
}