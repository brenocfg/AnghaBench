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
struct TYPE_2__ {scalar_t__ cidx; scalar_t__ size; int /*<<< orphan*/  in_use; } ;
struct t4_wq {TYPE_1__ rq; } ;

/* Variables and functions */

__attribute__((used)) static inline void t4_rq_consume(struct t4_wq *wq)
{
	wq->rq.in_use--;
	if (++wq->rq.cidx == wq->rq.size)
		wq->rq.cidx = 0;
}