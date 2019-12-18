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
struct sge_txq {int cidx; scalar_t__ size; TYPE_1__* stat; } ;
struct TYPE_2__ {int /*<<< orphan*/  cidx; } ;

/* Variables and functions */
 int be16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int reclaimable(const struct sge_txq *tq)
{
	int hw_cidx = be16_to_cpu(tq->stat->cidx);
	int reclaimable = hw_cidx - tq->cidx;
	if (reclaimable < 0)
		reclaimable += tq->size;
	return reclaimable;
}