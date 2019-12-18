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
struct TYPE_2__ {int /*<<< orphan*/  qla_tgt; } ;
struct scsi_qla_host {TYPE_1__ vha_tgt; int /*<<< orphan*/  host_no; scalar_t__ fc_vport; } ;
struct qla_hw_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,int /*<<< orphan*/ ,struct qla_hw_data*) ; 
 int /*<<< orphan*/  ql_dbg_tgt ; 
 int /*<<< orphan*/  qlt_init_term_exchange (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qlt_release (int /*<<< orphan*/ ) ; 

int qlt_remove_target(struct qla_hw_data *ha, struct scsi_qla_host *vha)
{
	if (!vha->vha_tgt.qla_tgt)
		return 0;

	if (vha->fc_vport) {
		qlt_release(vha->vha_tgt.qla_tgt);
		return 0;
	}

	/* free left over qfull cmds */
	qlt_init_term_exchange(vha);

	ql_dbg(ql_dbg_tgt, vha, 0xe03c, "Unregistering target for host %ld(%p)",
	    vha->host_no, ha);
	qlt_release(vha->vha_tgt.qla_tgt);

	return 0;
}