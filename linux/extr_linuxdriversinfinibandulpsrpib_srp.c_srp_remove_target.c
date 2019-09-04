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
struct srp_target_port {scalar_t__ state; int ch_count; int /*<<< orphan*/  scsi_host; TYPE_1__* srp_host; int /*<<< orphan*/  list; struct srp_rdma_ch* ch; int /*<<< orphan*/  rport; int /*<<< orphan*/  tl_err_work; int /*<<< orphan*/  net; } ;
struct srp_rdma_ch {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  target_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_NS_TYPE_NET ; 
 scalar_t__ SRP_TARGET_REMOVED ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct srp_rdma_ch*) ; 
 int /*<<< orphan*/  kobj_ns_drop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_host_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_remove_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srp_del_scsi_host_attr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srp_disconnect_target (struct srp_target_port*) ; 
 int /*<<< orphan*/  srp_free_ch_ib (struct srp_target_port*,struct srp_rdma_ch*) ; 
 int /*<<< orphan*/  srp_free_req_data (struct srp_target_port*,struct srp_rdma_ch*) ; 
 int /*<<< orphan*/  srp_remove_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srp_rport_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srp_rport_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srp_stop_rport_timers (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void srp_remove_target(struct srp_target_port *target)
{
	struct srp_rdma_ch *ch;
	int i;

	WARN_ON_ONCE(target->state != SRP_TARGET_REMOVED);

	srp_del_scsi_host_attr(target->scsi_host);
	srp_rport_get(target->rport);
	srp_remove_host(target->scsi_host);
	scsi_remove_host(target->scsi_host);
	srp_stop_rport_timers(target->rport);
	srp_disconnect_target(target);
	kobj_ns_drop(KOBJ_NS_TYPE_NET, target->net);
	for (i = 0; i < target->ch_count; i++) {
		ch = &target->ch[i];
		srp_free_ch_ib(target, ch);
	}
	cancel_work_sync(&target->tl_err_work);
	srp_rport_put(target->rport);
	for (i = 0; i < target->ch_count; i++) {
		ch = &target->ch[i];
		srp_free_req_data(target, ch);
	}
	kfree(target->ch);
	target->ch = NULL;

	spin_lock(&target->srp_host->target_lock);
	list_del(&target->list);
	spin_unlock(&target->srp_host->target_lock);

	scsi_host_put(target->scsi_host);
}