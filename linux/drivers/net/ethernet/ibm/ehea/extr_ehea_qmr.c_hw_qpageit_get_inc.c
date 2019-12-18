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
typedef  int u64 ;
struct hw_queue {scalar_t__ current_q_offset; scalar_t__ pagesize; scalar_t__ queue_length; } ;

/* Variables and functions */
 int EHEA_PAGESIZE ; 
 void* hw_qeit_get (struct hw_queue*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void *hw_qpageit_get_inc(struct hw_queue *queue)
{
	void *retvalue = hw_qeit_get(queue);

	queue->current_q_offset += queue->pagesize;
	if (queue->current_q_offset > queue->queue_length) {
		queue->current_q_offset -= queue->pagesize;
		retvalue = NULL;
	} else if (((u64) retvalue) & (EHEA_PAGESIZE-1)) {
		pr_err("not on pageboundary\n");
		retvalue = NULL;
	}
	return retvalue;
}