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
struct ionic_cq {int done_color; TYPE_1__* tail; } ;
struct TYPE_2__ {struct TYPE_2__* next; scalar_t__ last; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_STATS_CQE_CNT (struct ionic_cq*) ; 
 scalar_t__ ionic_rx_service (struct ionic_cq*,TYPE_1__*) ; 

__attribute__((used)) static u32 ionic_rx_walk_cq(struct ionic_cq *rxcq, u32 limit)
{
	u32 work_done = 0;

	while (ionic_rx_service(rxcq, rxcq->tail)) {
		if (rxcq->tail->last)
			rxcq->done_color = !rxcq->done_color;
		rxcq->tail = rxcq->tail->next;
		DEBUG_STATS_CQE_CNT(rxcq);

		if (++work_done >= limit)
			break;
	}

	return work_done;
}