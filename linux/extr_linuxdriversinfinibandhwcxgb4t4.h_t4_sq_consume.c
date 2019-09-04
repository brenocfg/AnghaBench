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
struct TYPE_2__ {scalar_t__ cidx; scalar_t__ flush_cidx; scalar_t__ size; int /*<<< orphan*/  in_use; } ;
struct t4_wq {TYPE_1__ sq; } ;

/* Variables and functions */

__attribute__((used)) static inline void t4_sq_consume(struct t4_wq *wq)
{
	if (wq->sq.cidx == wq->sq.flush_cidx)
		wq->sq.flush_cidx = -1;
	wq->sq.in_use--;
	if (++wq->sq.cidx == wq->sq.size)
		wq->sq.cidx = 0;
}