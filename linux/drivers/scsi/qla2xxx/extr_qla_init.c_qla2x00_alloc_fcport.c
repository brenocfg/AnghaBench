#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct ct_sns_pkt {int dummy; } ;
struct TYPE_17__ {TYPE_3__* hw; } ;
typedef  TYPE_5__ scsi_qla_host_t ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_16__ {int /*<<< orphan*/  ct_sns; int /*<<< orphan*/  ct_sns_dma; } ;
struct TYPE_18__ {int logout_on_delete; int /*<<< orphan*/  list; int /*<<< orphan*/  gnl_entry; int /*<<< orphan*/  reg_work; int /*<<< orphan*/  del_work; TYPE_4__ ct_desc; int /*<<< orphan*/  chip_reset; int /*<<< orphan*/  login_retry; int /*<<< orphan*/  deleted; int /*<<< orphan*/  fw_login_state; int /*<<< orphan*/  disc_state; int /*<<< orphan*/  fp_speed; int /*<<< orphan*/  supported_classes; int /*<<< orphan*/  loop_id; int /*<<< orphan*/  port_type; TYPE_5__* vha; } ;
typedef  TYPE_6__ fc_port_t ;
struct TYPE_15__ {TYPE_2__* base_qpair; int /*<<< orphan*/  login_retry_count; TYPE_1__* pdev; } ;
struct TYPE_14__ {int /*<<< orphan*/  chip_reset; } ;
struct TYPE_13__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSC_DELETED ; 
 int /*<<< orphan*/  DSC_LS_PORT_UNAVAIL ; 
 int /*<<< orphan*/  FCS_UNCONFIGURED ; 
 int /*<<< orphan*/  FCT_UNKNOWN ; 
 int /*<<< orphan*/  FC_COS_UNSPECIFIED ; 
 int /*<<< orphan*/  FC_NO_LOOP_ID ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PORT_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  QLA_SESS_DELETED ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_6__*) ; 
 TYPE_6__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_5__*,int,char*) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int /*<<< orphan*/  qla24xx_delete_sess_fn ; 
 int /*<<< orphan*/  qla2x00_set_fcport_state (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla_register_fcport_fn ; 

fc_port_t *
qla2x00_alloc_fcport(scsi_qla_host_t *vha, gfp_t flags)
{
	fc_port_t *fcport;

	fcport = kzalloc(sizeof(fc_port_t), flags);
	if (!fcport)
		return NULL;

	fcport->ct_desc.ct_sns = dma_alloc_coherent(&vha->hw->pdev->dev,
		sizeof(struct ct_sns_pkt), &fcport->ct_desc.ct_sns_dma,
		flags);
	if (!fcport->ct_desc.ct_sns) {
		ql_log(ql_log_warn, vha, 0xd049,
		    "Failed to allocate ct_sns request.\n");
		kfree(fcport);
		return NULL;
	}

	/* Setup fcport template structure. */
	fcport->vha = vha;
	fcport->port_type = FCT_UNKNOWN;
	fcport->loop_id = FC_NO_LOOP_ID;
	qla2x00_set_fcport_state(fcport, FCS_UNCONFIGURED);
	fcport->supported_classes = FC_COS_UNSPECIFIED;
	fcport->fp_speed = PORT_SPEED_UNKNOWN;

	fcport->disc_state = DSC_DELETED;
	fcport->fw_login_state = DSC_LS_PORT_UNAVAIL;
	fcport->deleted = QLA_SESS_DELETED;
	fcport->login_retry = vha->hw->login_retry_count;
	fcport->chip_reset = vha->hw->base_qpair->chip_reset;
	fcport->logout_on_delete = 1;

	if (!fcport->ct_desc.ct_sns) {
		ql_log(ql_log_warn, vha, 0xd049,
		    "Failed to allocate ct_sns request.\n");
		kfree(fcport);
		return NULL;
	}

	INIT_WORK(&fcport->del_work, qla24xx_delete_sess_fn);
	INIT_WORK(&fcport->reg_work, qla_register_fcport_fn);
	INIT_LIST_HEAD(&fcport->gnl_entry);
	INIT_LIST_HEAD(&fcport->list);

	return fcport;
}