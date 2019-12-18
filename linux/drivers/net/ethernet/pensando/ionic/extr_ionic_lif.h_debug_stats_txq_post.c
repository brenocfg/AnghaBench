#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct ionic_txq_desc {int /*<<< orphan*/  cmd; } ;
struct TYPE_4__ {int dbell_count; } ;
struct ionic_qcq {TYPE_3__* stats; TYPE_1__ q; } ;
struct TYPE_5__ {int /*<<< orphan*/ * sg_cntr; } ;
struct TYPE_6__ {TYPE_2__ tx; } ;

/* Variables and functions */
 int IONIC_MAX_NUM_SG_CNTR ; 
 int IONIC_TXQ_DESC_NSGE_MASK ; 
 int IONIC_TXQ_DESC_NSGE_SHIFT ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void debug_stats_txq_post(struct ionic_qcq *qcq,
					struct ionic_txq_desc *desc, bool dbell)
{
	u8 num_sg_elems = ((le64_to_cpu(desc->cmd) >> IONIC_TXQ_DESC_NSGE_SHIFT)
						& IONIC_TXQ_DESC_NSGE_MASK);

	qcq->q.dbell_count += dbell;

	if (num_sg_elems > (IONIC_MAX_NUM_SG_CNTR - 1))
		num_sg_elems = IONIC_MAX_NUM_SG_CNTR - 1;

	qcq->stats->tx.sg_cntr[num_sg_elems]++;
}