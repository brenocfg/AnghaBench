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
struct timer_list {int dummy; } ;
struct qeth_qdio_out_q {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_TXQ_STAT_INC (struct qeth_qdio_out_q*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  completion_timer ; 
 struct qeth_qdio_out_q* from_timer (int /*<<< orphan*/ ,struct timer_list*,struct timer_list*) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 struct qeth_qdio_out_q* queue ; 

__attribute__((used)) static void qeth_tx_completion_timer(struct timer_list *timer)
{
	struct qeth_qdio_out_q *queue = from_timer(queue, timer, timer);

	napi_schedule(&queue->napi);
	QETH_TXQ_STAT_INC(queue, completion_timer);
}