#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_17__ ;
typedef  struct TYPE_18__   TYPE_11__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  size_t uint16_t ;
struct TYPE_26__ {scalar_t__ rsvd_1; } ;
struct TYPE_19__ {TYPE_7__ b; } ;
struct TYPE_27__ {int fc4f_nvme; TYPE_17__ d_id; int /*<<< orphan*/  fc4_type; } ;
typedef  TYPE_8__ sw_info_t ;
struct qla_hw_data {size_t max_fibre_devices; int /*<<< orphan*/  ms_iocb_dma; int /*<<< orphan*/  ms_iocb; TYPE_11__* ct_sns; TYPE_1__* isp_ops; int /*<<< orphan*/  ct_sns_dma; } ;
struct TYPE_24__ {int* fc4_features; } ;
struct TYPE_25__ {TYPE_5__ gff_id; } ;
struct ct_sns_rsp {TYPE_6__ rsp; } ;
struct TYPE_22__ {int /*<<< orphan*/  port_id; } ;
struct TYPE_23__ {TYPE_3__ port_id; } ;
struct ct_sns_req {TYPE_4__ req; } ;
struct ct_arg {int /*<<< orphan*/  nport_handle; int /*<<< orphan*/  rsp_size; int /*<<< orphan*/  req_size; int /*<<< orphan*/  rsp_dma; int /*<<< orphan*/  req_dma; int /*<<< orphan*/  iocb; } ;
struct TYPE_28__ {struct qla_hw_data* hw; } ;
typedef  TYPE_9__ scsi_qla_host_t ;
typedef  int /*<<< orphan*/  ms_iocb_entry_t ;
struct TYPE_21__ {struct ct_sns_rsp rsp; } ;
struct TYPE_20__ {int /*<<< orphan*/ * (* prep_ms_iocb ) (TYPE_9__*,struct ct_arg*) ;} ;
struct TYPE_18__ {TYPE_2__ p; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC4_TYPE_FCP_SCSI ; 
 int /*<<< orphan*/  FC4_TYPE_OTHER ; 
 int /*<<< orphan*/  FC4_TYPE_UNKNOWN ; 
 size_t GFF_FCP_SCSI_OFFSET ; 
 int /*<<< orphan*/  GFF_ID_CMD ; 
 int /*<<< orphan*/  GFF_ID_REQ_SIZE ; 
 int /*<<< orphan*/  GFF_ID_RSP_SIZE ; 
 size_t GFF_NVME_OFFSET ; 
 int /*<<< orphan*/  IS_FWI2_CAPABLE (struct qla_hw_data*) ; 
 int /*<<< orphan*/  NPH_SNS ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  port_id_to_be_id (TYPE_17__) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_9__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_dbg_disc ; 
 int qla2x00_chk_ms_status (TYPE_9__*,int /*<<< orphan*/ *,struct ct_sns_rsp*,char*) ; 
 int qla2x00_issue_iocb (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ct_sns_req* qla2x00_prep_ct_req (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (TYPE_9__*,struct ct_arg*) ; 

void
qla2x00_gff_id(scsi_qla_host_t *vha, sw_info_t *list)
{
	int		rval;
	uint16_t	i;

	ms_iocb_entry_t	*ms_pkt;
	struct ct_sns_req	*ct_req;
	struct ct_sns_rsp	*ct_rsp;
	struct qla_hw_data *ha = vha->hw;
	uint8_t fcp_scsi_features = 0;
	struct ct_arg arg;

	for (i = 0; i < ha->max_fibre_devices; i++) {
		/* Set default FC4 Type as UNKNOWN so the default is to
		 * Process this port */
		list[i].fc4_type = FC4_TYPE_UNKNOWN;

		/* Do not attempt GFF_ID if we are not FWI_2 capable */
		if (!IS_FWI2_CAPABLE(ha))
			continue;

		arg.iocb = ha->ms_iocb;
		arg.req_dma = ha->ct_sns_dma;
		arg.rsp_dma = ha->ct_sns_dma;
		arg.req_size = GFF_ID_REQ_SIZE;
		arg.rsp_size = GFF_ID_RSP_SIZE;
		arg.nport_handle = NPH_SNS;

		/* Prepare common MS IOCB */
		ms_pkt = ha->isp_ops->prep_ms_iocb(vha, &arg);

		/* Prepare CT request */
		ct_req = qla2x00_prep_ct_req(ha->ct_sns, GFF_ID_CMD,
		    GFF_ID_RSP_SIZE);
		ct_rsp = &ha->ct_sns->p.rsp;

		/* Prepare CT arguments -- port_id */
		ct_req->req.port_id.port_id = port_id_to_be_id(list[i].d_id);

		/* Execute MS IOCB */
		rval = qla2x00_issue_iocb(vha, ha->ms_iocb, ha->ms_iocb_dma,
		   sizeof(ms_iocb_entry_t));

		if (rval != QLA_SUCCESS) {
			ql_dbg(ql_dbg_disc, vha, 0x205c,
			    "GFF_ID issue IOCB failed (%d).\n", rval);
		} else if (qla2x00_chk_ms_status(vha, ms_pkt, ct_rsp,
			       "GFF_ID") != QLA_SUCCESS) {
			ql_dbg(ql_dbg_disc, vha, 0x205d,
			    "GFF_ID IOCB status had a failure status code.\n");
		} else {
			fcp_scsi_features =
			   ct_rsp->rsp.gff_id.fc4_features[GFF_FCP_SCSI_OFFSET];
			fcp_scsi_features &= 0x0f;

			if (fcp_scsi_features)
				list[i].fc4_type = FC4_TYPE_FCP_SCSI;
			else
				list[i].fc4_type = FC4_TYPE_OTHER;

			list[i].fc4f_nvme =
			    ct_rsp->rsp.gff_id.fc4_features[GFF_NVME_OFFSET];
			list[i].fc4f_nvme &= 0xf;
		}

		/* Last device exit. */
		if (list[i].d_id.b.rsvd_1 != 0)
			break;
	}
}