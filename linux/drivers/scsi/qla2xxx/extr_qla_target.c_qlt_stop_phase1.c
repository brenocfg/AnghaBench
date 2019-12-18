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
struct TYPE_3__ {int /*<<< orphan*/  tgt_mutex; } ;
struct scsi_qla_host {TYPE_1__ vha_tgt; struct qla_tgt* host_no; } ;
struct qla_tgt {int tgt_stop; int /*<<< orphan*/  waitQ; struct scsi_qla_host* sess_count; int /*<<< orphan*/  sess_work_lock; int /*<<< orphan*/  sess_works_list; scalar_t__ tgt_stopped; struct qla_hw_data* ha; struct scsi_qla_host* vha; } ;
struct TYPE_4__ {int /*<<< orphan*/  host_shutting_down; } ;
struct qla_hw_data {int /*<<< orphan*/  optrom_mutex; TYPE_2__ flags; } ;

/* Variables and functions */
 int EPERM ; 
 int HZ ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,...) ; 
 int /*<<< orphan*/  ql_dbg_tgt_mgt ; 
 scalar_t__ qla_dual_mode_enabled (struct scsi_qla_host*) ; 
 scalar_t__ qla_tgt_mode_enabled (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla_tgt_mutex ; 
 int /*<<< orphan*/  qlt_clear_tgt_db (struct qla_tgt*) ; 
 int /*<<< orphan*/  qlt_disable_vha (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_tgt_sess_count (struct qla_tgt*) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int qlt_stop_phase1(struct qla_tgt *tgt)
{
	struct scsi_qla_host *vha = tgt->vha;
	struct qla_hw_data *ha = tgt->ha;
	unsigned long flags;

	mutex_lock(&ha->optrom_mutex);
	mutex_lock(&qla_tgt_mutex);

	if (tgt->tgt_stop || tgt->tgt_stopped) {
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf04e,
		    "Already in tgt->tgt_stop or tgt_stopped state\n");
		mutex_unlock(&qla_tgt_mutex);
		mutex_unlock(&ha->optrom_mutex);
		return -EPERM;
	}

	ql_dbg(ql_dbg_tgt_mgt, vha, 0xe003, "Stopping target for host %ld(%p)\n",
	    vha->host_no, vha);
	/*
	 * Mutex needed to sync with qla_tgt_fc_port_[added,deleted].
	 * Lock is needed, because we still can get an incoming packet.
	 */
	mutex_lock(&vha->vha_tgt.tgt_mutex);
	tgt->tgt_stop = 1;
	qlt_clear_tgt_db(tgt);
	mutex_unlock(&vha->vha_tgt.tgt_mutex);
	mutex_unlock(&qla_tgt_mutex);

	ql_dbg(ql_dbg_tgt_mgt, vha, 0xf009,
	    "Waiting for sess works (tgt %p)", tgt);
	spin_lock_irqsave(&tgt->sess_work_lock, flags);
	while (!list_empty(&tgt->sess_works_list)) {
		spin_unlock_irqrestore(&tgt->sess_work_lock, flags);
		flush_scheduled_work();
		spin_lock_irqsave(&tgt->sess_work_lock, flags);
	}
	spin_unlock_irqrestore(&tgt->sess_work_lock, flags);

	ql_dbg(ql_dbg_tgt_mgt, vha, 0xf00a,
	    "Waiting for tgt %p: sess_count=%d\n", tgt, tgt->sess_count);

	wait_event_timeout(tgt->waitQ, test_tgt_sess_count(tgt), 10*HZ);

	/* Big hammer */
	if (!ha->flags.host_shutting_down &&
	    (qla_tgt_mode_enabled(vha) || qla_dual_mode_enabled(vha)))
		qlt_disable_vha(vha);

	/* Wait for sessions to clear out (just in case) */
	wait_event_timeout(tgt->waitQ, test_tgt_sess_count(tgt), 10*HZ);
	mutex_unlock(&ha->optrom_mutex);

	return 0;
}