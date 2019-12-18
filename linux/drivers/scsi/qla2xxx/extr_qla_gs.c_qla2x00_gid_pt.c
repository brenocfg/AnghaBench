#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_20__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_13__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct TYPE_29__ {int rsvd_1; } ;
struct TYPE_23__ {TYPE_7__ b; } ;
struct TYPE_30__ {TYPE_20__ d_id; int /*<<< orphan*/  fp_speed; int /*<<< orphan*/  fabric_port_name; } ;
typedef  TYPE_8__ sw_info_t ;
struct qla_hw_data {size_t max_fibre_devices; int /*<<< orphan*/  ms_iocb_dma; int /*<<< orphan*/  ms_iocb; TYPE_13__* ct_sns; TYPE_1__* isp_ops; int /*<<< orphan*/  ct_sns_dma; } ;
struct TYPE_27__ {struct ct_sns_gid_pt_data* entries; } ;
struct TYPE_28__ {TYPE_5__ gid_pt; } ;
struct ct_sns_rsp {TYPE_6__ rsp; } ;
struct TYPE_25__ {int /*<<< orphan*/  port_type; } ;
struct TYPE_26__ {TYPE_3__ gid_pt; } ;
struct ct_sns_req {TYPE_4__ req; } ;
struct ct_sns_gid_pt_data {int control_byte; int /*<<< orphan*/  port_id; } ;
struct ct_arg {size_t rsp_size; int /*<<< orphan*/  nport_handle; int /*<<< orphan*/  req_size; int /*<<< orphan*/  rsp_dma; int /*<<< orphan*/  req_dma; int /*<<< orphan*/  iocb; } ;
struct TYPE_31__ {struct qla_hw_data* hw; } ;
typedef  TYPE_9__ scsi_qla_host_t ;
typedef  int /*<<< orphan*/  ms_iocb_entry_t ;
struct TYPE_24__ {struct ct_sns_rsp rsp; } ;
struct TYPE_22__ {int /*<<< orphan*/ * (* prep_ms_iocb ) (TYPE_9__*,struct ct_arg*) ;} ;
struct TYPE_21__ {TYPE_2__ p; } ;

/* Variables and functions */
 int BIT_7 ; 
 int /*<<< orphan*/  GID_PT_CMD ; 
 int /*<<< orphan*/  GID_PT_REQ_SIZE ; 
 scalar_t__ IS_QLA2100 (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA2200 (struct qla_hw_data*) ; 
 int /*<<< orphan*/  NPH_SNS ; 
 int /*<<< orphan*/  NS_NX_PORT_TYPE ; 
 int /*<<< orphan*/  PORT_SPEED_UNKNOWN ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  WWN_SIZE ; 
 TYPE_20__ be_to_port_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_9__*,int,char*,int) ; 
 int /*<<< orphan*/  ql_dbg_disc ; 
 int qla2x00_chk_ms_status (TYPE_9__*,int /*<<< orphan*/ *,struct ct_sns_rsp*,char*) ; 
 size_t qla2x00_gid_pt_rsp_size (TYPE_9__*) ; 
 int qla2x00_issue_iocb (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ct_sns_req* qla2x00_prep_ct_req (TYPE_13__*,int /*<<< orphan*/ ,size_t) ; 
 int qla2x00_sns_gid_pt (TYPE_9__*,TYPE_8__*) ; 
 int /*<<< orphan*/ * stub1 (TYPE_9__*,struct ct_arg*) ; 

int
qla2x00_gid_pt(scsi_qla_host_t *vha, sw_info_t *list)
{
	int		rval;
	uint16_t	i;

	ms_iocb_entry_t	*ms_pkt;
	struct ct_sns_req	*ct_req;
	struct ct_sns_rsp	*ct_rsp;

	struct ct_sns_gid_pt_data *gid_data;
	struct qla_hw_data *ha = vha->hw;
	uint16_t gid_pt_rsp_size;
	struct ct_arg arg;

	if (IS_QLA2100(ha) || IS_QLA2200(ha))
		return qla2x00_sns_gid_pt(vha, list);

	gid_data = NULL;
	gid_pt_rsp_size = qla2x00_gid_pt_rsp_size(vha);

	arg.iocb = ha->ms_iocb;
	arg.req_dma = ha->ct_sns_dma;
	arg.rsp_dma = ha->ct_sns_dma;
	arg.req_size = GID_PT_REQ_SIZE;
	arg.rsp_size = gid_pt_rsp_size;
	arg.nport_handle = NPH_SNS;

	/* Issue GID_PT */
	/* Prepare common MS IOCB */
	ms_pkt = ha->isp_ops->prep_ms_iocb(vha, &arg);

	/* Prepare CT request */
	ct_req = qla2x00_prep_ct_req(ha->ct_sns, GID_PT_CMD, gid_pt_rsp_size);
	ct_rsp = &ha->ct_sns->p.rsp;

	/* Prepare CT arguments -- port_type */
	ct_req->req.gid_pt.port_type = NS_NX_PORT_TYPE;

	/* Execute MS IOCB */
	rval = qla2x00_issue_iocb(vha, ha->ms_iocb, ha->ms_iocb_dma,
	    sizeof(ms_iocb_entry_t));
	if (rval != QLA_SUCCESS) {
		/*EMPTY*/
		ql_dbg(ql_dbg_disc, vha, 0x2055,
		    "GID_PT issue IOCB failed (%d).\n", rval);
	} else if (qla2x00_chk_ms_status(vha, ms_pkt, ct_rsp, "GID_PT") !=
	    QLA_SUCCESS) {
		rval = QLA_FUNCTION_FAILED;
	} else {
		/* Set port IDs in switch info list. */
		for (i = 0; i < ha->max_fibre_devices; i++) {
			gid_data = &ct_rsp->rsp.gid_pt.entries[i];
			list[i].d_id = be_to_port_id(gid_data->port_id);
			memset(list[i].fabric_port_name, 0, WWN_SIZE);
			list[i].fp_speed = PORT_SPEED_UNKNOWN;

			/* Last one exit. */
			if (gid_data->control_byte & BIT_7) {
				list[i].d_id.b.rsvd_1 = gid_data->control_byte;
				break;
			}
		}

		/*
		 * If we've used all available slots, then the switch is
		 * reporting back more devices than we can handle with this
		 * single call.  Return a failed status, and let GA_NXT handle
		 * the overload.
		 */
		if (i == ha->max_fibre_devices)
			rval = QLA_FUNCTION_FAILED;
	}

	return (rval);
}