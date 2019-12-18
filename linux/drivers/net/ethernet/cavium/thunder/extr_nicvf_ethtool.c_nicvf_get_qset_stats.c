#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
struct nicvf {TYPE_3__* qs; } ;
struct ethtool_stats {int dummy; } ;
struct TYPE_8__ {size_t index; } ;
struct TYPE_7__ {int rq_cnt; int sq_cnt; TYPE_2__* sq; TYPE_1__* rq; } ;
struct TYPE_6__ {int /*<<< orphan*/  stats; } ;
struct TYPE_5__ {int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int nicvf_n_queue_stats ; 
 TYPE_4__* nicvf_queue_stats ; 
 int /*<<< orphan*/  nicvf_update_rq_stats (struct nicvf*,int) ; 
 int /*<<< orphan*/  nicvf_update_sq_stats (struct nicvf*,int) ; 

__attribute__((used)) static void nicvf_get_qset_stats(struct nicvf *nic,
				 struct ethtool_stats *stats, u64 **data)
{
	int stat, qidx;

	if (!nic)
		return;

	for (qidx = 0; qidx < nic->qs->rq_cnt; qidx++) {
		nicvf_update_rq_stats(nic, qidx);
		for (stat = 0; stat < nicvf_n_queue_stats; stat++)
			*((*data)++) = ((u64 *)&nic->qs->rq[qidx].stats)
					[nicvf_queue_stats[stat].index];
	}

	for (qidx = 0; qidx < nic->qs->sq_cnt; qidx++) {
		nicvf_update_sq_stats(nic, qidx);
		for (stat = 0; stat < nicvf_n_queue_stats; stat++)
			*((*data)++) = ((u64 *)&nic->qs->sq[qidx].stats)
					[nicvf_queue_stats[stat].index];
	}
}