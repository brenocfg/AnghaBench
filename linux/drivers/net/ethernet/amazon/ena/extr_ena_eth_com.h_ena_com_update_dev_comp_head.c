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
typedef  int u16 ;
struct ena_com_io_cq {int cq_head_db_reg; int head; int last_head_update; int q_depth; int /*<<< orphan*/  qid; } ;

/* Variables and functions */
 int ENA_COMP_HEAD_THRESH ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writel (int,int) ; 

__attribute__((used)) static inline int ena_com_update_dev_comp_head(struct ena_com_io_cq *io_cq)
{
	u16 unreported_comp, head;
	bool need_update;

	if (unlikely(io_cq->cq_head_db_reg)) {
		head = io_cq->head;
		unreported_comp = head - io_cq->last_head_update;
		need_update = unreported_comp > (io_cq->q_depth / ENA_COMP_HEAD_THRESH);

		if (unlikely(need_update)) {
			pr_debug("Write completion queue doorbell for queue %d: head: %d\n",
				 io_cq->qid, head);
			writel(head, io_cq->cq_head_db_reg);
			io_cq->last_head_update = head;
		}
	}

	return 0;
}