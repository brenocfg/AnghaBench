#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_10__ {int /*<<< orphan*/  tgt_mutex; TYPE_1__* qla_tgt; } ;
struct scsi_qla_host {int vp_idx; TYPE_2__ vha_tgt; } ;
struct fc_port {int dummy; } ;
struct TYPE_11__ {int cmd_count; int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ qlt_port_logo_t ;
typedef  int /*<<< orphan*/  fc_port_t ;
struct TYPE_12__ {int domain; int area; int al_pa; } ;
typedef  TYPE_4__ be_id_t ;
struct TYPE_9__ {int /*<<< orphan*/  tgt_global_resets_count; } ;

/* Variables and functions */
 int ENOENT ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be_to_port_id (TYPE_4__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,int,int,int) ; 
 int /*<<< orphan*/  ql_dbg_tgt_mgt ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,int,int,int,int) ; 
 int /*<<< orphan*/  ql_log_info ; 
 int qla24xx_get_loop_id (struct scsi_qla_host*,TYPE_4__,int /*<<< orphan*/ *) ; 
 struct fc_port* qlt_create_sess (struct scsi_qla_host*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * qlt_get_port_database (struct scsi_qla_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlt_send_first_logo (struct scsi_qla_host*,TYPE_3__*) ; 

__attribute__((used)) static struct fc_port *qlt_make_local_sess(struct scsi_qla_host *vha,
					   be_id_t s_id)
{
	struct fc_port *sess = NULL;
	fc_port_t *fcport = NULL;
	int rc, global_resets;
	uint16_t loop_id = 0;

	if (s_id.domain == 0xFF && s_id.area == 0xFC) {
		/*
		 * This is Domain Controller, so it should be
		 * OK to drop SCSI commands from it.
		 */
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf042,
		    "Unable to find initiator with S_ID %x:%x:%x",
		    s_id.domain, s_id.area, s_id.al_pa);
		return NULL;
	}

	mutex_lock(&vha->vha_tgt.tgt_mutex);

retry:
	global_resets =
	    atomic_read(&vha->vha_tgt.qla_tgt->tgt_global_resets_count);

	rc = qla24xx_get_loop_id(vha, s_id, &loop_id);
	if (rc != 0) {
		mutex_unlock(&vha->vha_tgt.tgt_mutex);

		ql_log(ql_log_info, vha, 0xf071,
		    "qla_target(%d): Unable to find "
		    "initiator with S_ID %x:%x:%x",
		    vha->vp_idx, s_id.domain, s_id.area, s_id.al_pa);

		if (rc == -ENOENT) {
			qlt_port_logo_t logo;

			logo.id = be_to_port_id(s_id);
			logo.cmd_count = 1;
			qlt_send_first_logo(vha, &logo);
		}

		return NULL;
	}

	fcport = qlt_get_port_database(vha, loop_id);
	if (!fcport) {
		mutex_unlock(&vha->vha_tgt.tgt_mutex);
		return NULL;
	}

	if (global_resets !=
	    atomic_read(&vha->vha_tgt.qla_tgt->tgt_global_resets_count)) {
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf043,
		    "qla_target(%d): global reset during session discovery "
		    "(counter was %d, new %d), retrying", vha->vp_idx,
		    global_resets,
		    atomic_read(&vha->vha_tgt.
			qla_tgt->tgt_global_resets_count));
		goto retry;
	}

	sess = qlt_create_sess(vha, fcport, true);

	mutex_unlock(&vha->vha_tgt.tgt_mutex);

	return sess;
}