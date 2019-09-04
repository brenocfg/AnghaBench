#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct t4_srq {int pidx; int size; int wq_pidx; TYPE_2__* queue; int /*<<< orphan*/  in_use; } ;
struct TYPE_3__ {int host_pidx; } ;
struct TYPE_4__ {TYPE_1__ status; } ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T4_EQ_ENTRY_SIZE ; 
 int T4_RQ_NUM_SLOTS ; 

__attribute__((used)) static inline void t4_srq_produce(struct t4_srq *srq, u8 len16)
{
	srq->in_use++;
	if (++srq->pidx == srq->size)
		srq->pidx = 0;
	srq->wq_pidx += DIV_ROUND_UP(len16 * 16, T4_EQ_ENTRY_SIZE);
	if (srq->wq_pidx >= srq->size * T4_RQ_NUM_SLOTS)
		srq->wq_pidx %= srq->size * T4_RQ_NUM_SLOTS;
	srq->queue[srq->size].status.host_pidx = srq->pidx;
}