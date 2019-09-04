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
struct snd_queue {TYPE_2__ stats; } ;
struct nicvf {TYPE_1__* qs; } ;
struct TYPE_3__ {struct snd_queue* sq; } ;

/* Variables and functions */
 int NIC_QSET_SQ_0_7_STAT_0_1 ; 
 int NIC_Q_NUM_SHIFT ; 
 int RQ_SQ_STATS_OCTS ; 
 int RQ_SQ_STATS_PKTS ; 
 void* nicvf_reg_read (struct nicvf*,int) ; 

void nicvf_update_sq_stats(struct nicvf *nic, int sq_idx)
{
	struct snd_queue *sq;

#define GET_SQ_STATS(reg) \
	nicvf_reg_read(nic, NIC_QSET_SQ_0_7_STAT_0_1 |\
			    (sq_idx << NIC_Q_NUM_SHIFT) | (reg << 3))

	sq = &nic->qs->sq[sq_idx];
	sq->stats.bytes = GET_SQ_STATS(RQ_SQ_STATS_OCTS);
	sq->stats.pkts = GET_SQ_STATS(RQ_SQ_STATS_PKTS);
}