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
struct t4_srq {size_t cidx; size_t size; int /*<<< orphan*/  ooo_count; TYPE_2__* queue; } ;
struct TYPE_3__ {size_t host_cidx; } ;
struct TYPE_4__ {TYPE_1__ status; } ;

/* Variables and functions */

__attribute__((used)) static inline void t4_srq_consume_ooo(struct t4_srq *srq)
{
	srq->cidx++;
	if (srq->cidx == srq->size)
		srq->cidx  = 0;
	srq->queue[srq->size].status.host_cidx = srq->cidx;
	srq->ooo_count--;
}