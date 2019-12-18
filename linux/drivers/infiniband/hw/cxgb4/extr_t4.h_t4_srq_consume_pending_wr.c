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
struct t4_srq {scalar_t__ pending_cidx; scalar_t__ size; int /*<<< orphan*/  in_use; int /*<<< orphan*/  pending_in_use; } ;

/* Variables and functions */

__attribute__((used)) static inline void t4_srq_consume_pending_wr(struct t4_srq *srq)
{
	srq->pending_in_use--;
	srq->in_use--;
	if (++srq->pending_cidx == srq->size)
		srq->pending_cidx = 0;
}