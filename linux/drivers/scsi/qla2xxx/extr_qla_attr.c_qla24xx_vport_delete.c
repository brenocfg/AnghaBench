#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct qla_hw_data {TYPE_2__* pdev; int /*<<< orphan*/  vport_lock; int /*<<< orphan*/  vp_idx_map; int /*<<< orphan*/  cur_vport_count; } ;
struct fc_vport {TYPE_5__* dd_data; } ;
struct TYPE_20__ {int /*<<< orphan*/  l; } ;
struct TYPE_19__ {int /*<<< orphan*/ * l; int /*<<< orphan*/  ldma; int /*<<< orphan*/  size; } ;
struct TYPE_17__ {int delete_progress; } ;
struct TYPE_21__ {scalar_t__ vp_idx; int /*<<< orphan*/  host; TYPE_9__* qpair; TYPE_4__ scan; TYPE_3__ gnl; scalar_t__ timer_active; TYPE_1__ flags; int /*<<< orphan*/  dpc_flags; struct qla_hw_data* hw; } ;
typedef  TYPE_5__ scsi_qla_host_t ;
struct TYPE_22__ {scalar_t__ vp_idx; } ;
struct TYPE_18__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCPORT_UPDATE_NEEDED ; 
 int /*<<< orphan*/  LOOP_RESYNC_ACTIVE ; 
 scalar_t__ QLA_SUCCESS ; 
 int /*<<< orphan*/  VPORT_DELETE ; 
 int /*<<< orphan*/  clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_remove_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_5__*,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  ql_dbg_user ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_5__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_log_info ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int /*<<< orphan*/  qla24xx_deallocate_vp_id (TYPE_5__*) ; 
 int /*<<< orphan*/  qla24xx_disable_vp (TYPE_5__*) ; 
 int /*<<< orphan*/  qla2x00_free_fcports (TYPE_5__*) ; 
 int /*<<< orphan*/  qla2x00_vp_stop_timer (TYPE_5__*) ; 
 int /*<<< orphan*/  qla2x00_wait_for_sess_deletion (TYPE_5__*) ; 
 scalar_t__ qla2xxx_delete_qpair (TYPE_5__*,TYPE_9__*) ; 
 int /*<<< orphan*/  qla_nvme_delete (TYPE_5__*) ; 
 int /*<<< orphan*/  qlt_remove_target (struct qla_hw_data*,TYPE_5__*) ; 
 int /*<<< orphan*/  scsi_host_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_remove_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qla24xx_vport_delete(struct fc_vport *fc_vport)
{
	scsi_qla_host_t *vha = fc_vport->dd_data;
	struct qla_hw_data *ha = vha->hw;
	uint16_t id = vha->vp_idx;

	set_bit(VPORT_DELETE, &vha->dpc_flags);

	while (test_bit(LOOP_RESYNC_ACTIVE, &vha->dpc_flags) ||
	    test_bit(FCPORT_UPDATE_NEEDED, &vha->dpc_flags))
		msleep(1000);

	qla_nvme_delete(vha);

	qla24xx_disable_vp(vha);
	qla2x00_wait_for_sess_deletion(vha);

	vha->flags.delete_progress = 1;

	qlt_remove_target(ha, vha);

	fc_remove_host(vha->host);

	scsi_remove_host(vha->host);

	/* Allow timer to run to drain queued items, when removing vp */
	qla24xx_deallocate_vp_id(vha);

	if (vha->timer_active) {
		qla2x00_vp_stop_timer(vha);
		ql_dbg(ql_dbg_user, vha, 0x7086,
		    "Timer for the VP[%d] has stopped\n", vha->vp_idx);
	}

	qla2x00_free_fcports(vha);

	mutex_lock(&ha->vport_lock);
	ha->cur_vport_count--;
	clear_bit(vha->vp_idx, ha->vp_idx_map);
	mutex_unlock(&ha->vport_lock);

	dma_free_coherent(&ha->pdev->dev, vha->gnl.size, vha->gnl.l,
	    vha->gnl.ldma);

	vha->gnl.l = NULL;

	vfree(vha->scan.l);

	if (vha->qpair && vha->qpair->vp_idx == vha->vp_idx) {
		if (qla2xxx_delete_qpair(vha, vha->qpair) != QLA_SUCCESS)
			ql_log(ql_log_warn, vha, 0x7087,
			    "Queue Pair delete failed.\n");
	}

	ql_log(ql_log_info, vha, 0x7088, "VP[%d] deleted.\n", id);
	scsi_host_put(vha->host);
	return 0;
}