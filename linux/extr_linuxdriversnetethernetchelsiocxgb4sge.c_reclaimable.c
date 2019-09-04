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
struct sge_txq {int size; scalar_t__ cidx; TYPE_1__* stat; } ;
struct TYPE_2__ {int /*<<< orphan*/  cidx; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int reclaimable(const struct sge_txq *q)
{
	int hw_cidx = ntohs(READ_ONCE(q->stat->cidx));
	hw_cidx -= q->cidx;
	return hw_cidx < 0 ? hw_cidx + q->size : hw_cidx;
}