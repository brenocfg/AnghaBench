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
struct hw_queue {int current_q_offset; } ;
struct ehea_swqe {int dummy; } ;
struct ehea_qp {struct hw_queue hw_squeue; } ;

/* Variables and functions */
 int EHEA_SG_SQ ; 
 struct ehea_swqe* hw_qeit_get_inc (struct hw_queue*) ; 

__attribute__((used)) static inline struct ehea_swqe *ehea_get_swqe(struct ehea_qp *my_qp,
					      int *wqe_index)
{
	struct hw_queue *queue = &my_qp->hw_squeue;
	struct ehea_swqe *wqe_p;

	*wqe_index = (queue->current_q_offset) >> (7 + EHEA_SG_SQ);
	wqe_p = hw_qeit_get_inc(&my_qp->hw_squeue);

	return wqe_p;
}