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
typedef  scalar_t__ u64 ;
struct cfq_rb_root {int /*<<< orphan*/  min_vdisktime; } ;
struct cfq_queue {scalar_t__ slice_dispatch; scalar_t__ allocated_slice; int /*<<< orphan*/  nr_sectors; int /*<<< orphan*/  cfqd; } ;
struct TYPE_2__ {int count; } ;
struct cfq_group {int nr_cfqq; unsigned int vfraction; int /*<<< orphan*/  vdisktime; scalar_t__ saved_wl_slice; int /*<<< orphan*/  saved_wl_class; int /*<<< orphan*/  saved_wl_type; TYPE_1__ service_tree_idle; } ;
struct cfq_data {scalar_t__ workload_expires; int /*<<< orphan*/  serving_wl_class; int /*<<< orphan*/  serving_wl_type; struct cfq_rb_root grp_service_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ cfq_cfqq_slice_usage (struct cfq_queue*,scalar_t__*) ; 
 int /*<<< orphan*/  cfq_cfqq_sync (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_group_service_tree_add (struct cfq_rb_root*,struct cfq_group*) ; 
 int /*<<< orphan*/  cfq_group_service_tree_del (struct cfq_rb_root*,struct cfq_group*) ; 
 int /*<<< orphan*/  cfq_log_cfqg (struct cfq_data*,struct cfq_group*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfq_log_cfqq (int /*<<< orphan*/ ,struct cfq_queue*,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int cfqg_busy_async_queues (struct cfq_data*,struct cfq_group*) ; 
 scalar_t__ cfqg_scale_charge (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  cfqg_stats_set_start_empty_time (struct cfq_group*) ; 
 int /*<<< orphan*/  cfqg_stats_update_timeslice_used (struct cfq_group*,scalar_t__,scalar_t__) ; 
 scalar_t__ iops_mode (struct cfq_data*) ; 
 scalar_t__ ktime_get_ns () ; 

__attribute__((used)) static void cfq_group_served(struct cfq_data *cfqd, struct cfq_group *cfqg,
				struct cfq_queue *cfqq)
{
	struct cfq_rb_root *st = &cfqd->grp_service_tree;
	u64 used_sl, charge, unaccounted_sl = 0;
	int nr_sync = cfqg->nr_cfqq - cfqg_busy_async_queues(cfqd, cfqg)
			- cfqg->service_tree_idle.count;
	unsigned int vfr;
	u64 now = ktime_get_ns();

	BUG_ON(nr_sync < 0);
	used_sl = charge = cfq_cfqq_slice_usage(cfqq, &unaccounted_sl);

	if (iops_mode(cfqd))
		charge = cfqq->slice_dispatch;
	else if (!cfq_cfqq_sync(cfqq) && !nr_sync)
		charge = cfqq->allocated_slice;

	/*
	 * Can't update vdisktime while on service tree and cfqg->vfraction
	 * is valid only while on it.  Cache vfr, leave the service tree,
	 * update vdisktime and go back on.  The re-addition to the tree
	 * will also update the weights as necessary.
	 */
	vfr = cfqg->vfraction;
	cfq_group_service_tree_del(st, cfqg);
	cfqg->vdisktime += cfqg_scale_charge(charge, vfr);
	cfq_group_service_tree_add(st, cfqg);

	/* This group is being expired. Save the context */
	if (cfqd->workload_expires > now) {
		cfqg->saved_wl_slice = cfqd->workload_expires - now;
		cfqg->saved_wl_type = cfqd->serving_wl_type;
		cfqg->saved_wl_class = cfqd->serving_wl_class;
	} else
		cfqg->saved_wl_slice = 0;

	cfq_log_cfqg(cfqd, cfqg, "served: vt=%llu min_vt=%llu", cfqg->vdisktime,
					st->min_vdisktime);
	cfq_log_cfqq(cfqq->cfqd, cfqq,
		     "sl_used=%llu disp=%llu charge=%llu iops=%u sect=%lu",
		     used_sl, cfqq->slice_dispatch, charge,
		     iops_mode(cfqd), cfqq->nr_sectors);
	cfqg_stats_update_timeslice_used(cfqg, used_sl, unaccounted_sl);
	cfqg_stats_set_start_empty_time(cfqg);
}