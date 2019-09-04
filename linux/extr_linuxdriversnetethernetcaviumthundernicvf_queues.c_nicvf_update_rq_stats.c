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
struct TYPE_4__ {void* pkts; void* bytes; } ;
struct rcv_queue {TYPE_2__ stats; } ;
struct nicvf {TYPE_1__* qs; } ;
struct TYPE_3__ {struct rcv_queue* rq; } ;

/* Variables and functions */
 int NIC_QSET_RQ_0_7_STAT_0_1 ; 
 int NIC_Q_NUM_SHIFT ; 
 int RQ_SQ_STATS_OCTS ; 
 int RQ_SQ_STATS_PKTS ; 
 void* nicvf_reg_read (struct nicvf*,int) ; 

void nicvf_update_rq_stats(struct nicvf *nic, int rq_idx)
{
	struct rcv_queue *rq;

#define GET_RQ_STATS(reg) \
	nicvf_reg_read(nic, NIC_QSET_RQ_0_7_STAT_0_1 |\
			    (rq_idx << NIC_Q_NUM_SHIFT) | (reg << 3))

	rq = &nic->qs->rq[rq_idx];
	rq->stats.bytes = GET_RQ_STATS(RQ_SQ_STATS_OCTS);
	rq->stats.pkts = GET_RQ_STATS(RQ_SQ_STATS_PKTS);
}