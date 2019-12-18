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
struct TYPE_2__ {int /*<<< orphan*/ * work_done_cntr; int /*<<< orphan*/  poll_count; } ;
struct ionic_qcq {TYPE_1__ napi_stats; } ;

/* Variables and functions */
 int IONIC_MAX_NUM_NAPI_CNTR ; 

__attribute__((used)) static inline void debug_stats_napi_poll(struct ionic_qcq *qcq,
					 unsigned int work_done)
{
	qcq->napi_stats.poll_count++;

	if (work_done > (IONIC_MAX_NUM_NAPI_CNTR - 1))
		work_done = IONIC_MAX_NUM_NAPI_CNTR - 1;

	qcq->napi_stats.work_done_cntr[work_done]++;
}