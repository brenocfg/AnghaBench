#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct rsp_que {scalar_t__* in_ptr; scalar_t__ length; scalar_t__ ring; } ;
struct req_que {int num_outstanding_cmds; int current_outstanding_cmd; scalar_t__ length; scalar_t__ cnt; scalar_t__ ring_index; scalar_t__ ring; scalar_t__ ring_ptr; int /*<<< orphan*/ ** outstanding_cmds; scalar_t__* out_ptr; } ;
struct TYPE_17__ {int dport_enabled; int fawwpn_enabled; scalar_t__ npiv_supported; } ;
struct TYPE_14__ {scalar_t__ atio_ring_index; int /*<<< orphan*/  atio_ring; int /*<<< orphan*/  atio_ring_ptr; } ;
struct qla_hw_data {int max_req_queues; int max_rsp_queues; scalar_t__ operating_mode; int /*<<< orphan*/  init_cb_size; TYPE_4__ flags; scalar_t__ cur_fw_xcb_count; scalar_t__ max_npiv_vports; TYPE_2__* isp_ops; int /*<<< orphan*/  hardware_lock; TYPE_1__ tgt; int /*<<< orphan*/  rsp_qid_map; struct rsp_que** rsp_q_map; int /*<<< orphan*/  req_qid_map; struct req_que** req_q_map; scalar_t__ init_cb; } ;
struct TYPE_16__ {int firmware_options_1; void* execution_throttle; } ;
struct mid_init_cb_24xx {TYPE_3__ init_cb; void* options; void* count; } ;
struct TYPE_18__ {scalar_t__ u_ql2xiniexchg; scalar_t__ u_ql2xexchoffld; struct qla_hw_data* hw; } ;
typedef  TYPE_5__ scsi_qla_host_t ;
struct TYPE_15__ {int /*<<< orphan*/  (* update_fw_options ) (TYPE_5__*) ;int /*<<< orphan*/  (* config_rings ) (TYPE_5__*) ;} ;

/* Variables and functions */
 scalar_t__ BIT_1 ; 
 int BIT_6 ; 
 int BIT_7 ; 
 int /*<<< orphan*/  IS_CNA_CAPABLE (struct qla_hw_data*) ; 
 scalar_t__ IS_FWI2_CAPABLE (struct qla_hw_data*) ; 
 scalar_t__ IS_QLAFX00 (struct qla_hw_data*) ; 
 scalar_t__ LOOP ; 
 scalar_t__ MIN_MULTI_ID_FABRIC ; 
 int /*<<< orphan*/  QLA_FW_STARTED (struct qla_hw_data*) ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_5__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_dbg_init ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_5__*,int,char*) ; 
 int /*<<< orphan*/  ql_log_fatal ; 
 int qla2x00_init_firmware (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_init_response_q_entries (struct rsp_que*) ; 
 int qlafx00_init_firmware (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlafx00_init_response_q_entries (struct rsp_que*) ; 
 int /*<<< orphan*/  qlt_init_atio_q_entries (TYPE_5__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

int
qla2x00_init_rings(scsi_qla_host_t *vha)
{
	int	rval;
	unsigned long flags = 0;
	int cnt, que;
	struct qla_hw_data *ha = vha->hw;
	struct req_que *req;
	struct rsp_que *rsp;
	struct mid_init_cb_24xx *mid_init_cb =
	    (struct mid_init_cb_24xx *) ha->init_cb;

	spin_lock_irqsave(&ha->hardware_lock, flags);

	/* Clear outstanding commands array. */
	for (que = 0; que < ha->max_req_queues; que++) {
		req = ha->req_q_map[que];
		if (!req || !test_bit(que, ha->req_qid_map))
			continue;
		req->out_ptr = (void *)(req->ring + req->length);
		*req->out_ptr = 0;
		for (cnt = 1; cnt < req->num_outstanding_cmds; cnt++)
			req->outstanding_cmds[cnt] = NULL;

		req->current_outstanding_cmd = 1;

		/* Initialize firmware. */
		req->ring_ptr  = req->ring;
		req->ring_index    = 0;
		req->cnt      = req->length;
	}

	for (que = 0; que < ha->max_rsp_queues; que++) {
		rsp = ha->rsp_q_map[que];
		if (!rsp || !test_bit(que, ha->rsp_qid_map))
			continue;
		rsp->in_ptr = (void *)(rsp->ring + rsp->length);
		*rsp->in_ptr = 0;
		/* Initialize response queue entries */
		if (IS_QLAFX00(ha))
			qlafx00_init_response_q_entries(rsp);
		else
			qla2x00_init_response_q_entries(rsp);
	}

	ha->tgt.atio_ring_ptr = ha->tgt.atio_ring;
	ha->tgt.atio_ring_index = 0;
	/* Initialize ATIO queue entries */
	qlt_init_atio_q_entries(vha);

	ha->isp_ops->config_rings(vha);

	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	ql_dbg(ql_dbg_init, vha, 0x00d1, "Issue init firmware.\n");

	if (IS_QLAFX00(ha)) {
		rval = qlafx00_init_firmware(vha, ha->init_cb_size);
		goto next_check;
	}

	/* Update any ISP specific firmware options before initialization. */
	ha->isp_ops->update_fw_options(vha);

	if (ha->flags.npiv_supported) {
		if (ha->operating_mode == LOOP && !IS_CNA_CAPABLE(ha))
			ha->max_npiv_vports = MIN_MULTI_ID_FABRIC - 1;
		mid_init_cb->count = cpu_to_le16(ha->max_npiv_vports);
	}

	if (IS_FWI2_CAPABLE(ha)) {
		mid_init_cb->options = cpu_to_le16(BIT_1);
		mid_init_cb->init_cb.execution_throttle =
		    cpu_to_le16(ha->cur_fw_xcb_count);
		ha->flags.dport_enabled =
		    (mid_init_cb->init_cb.firmware_options_1 & BIT_7) != 0;
		ql_dbg(ql_dbg_init, vha, 0x0191, "DPORT Support: %s.\n",
		    (ha->flags.dport_enabled) ? "enabled" : "disabled");
		/* FA-WWPN Status */
		ha->flags.fawwpn_enabled =
		    (mid_init_cb->init_cb.firmware_options_1 & BIT_6) != 0;
		ql_dbg(ql_dbg_init, vha, 0x00bc, "FA-WWPN Support: %s.\n",
		    (ha->flags.fawwpn_enabled) ? "enabled" : "disabled");
	}

	rval = qla2x00_init_firmware(vha, ha->init_cb_size);
next_check:
	if (rval) {
		ql_log(ql_log_fatal, vha, 0x00d2,
		    "Init Firmware **** FAILED ****.\n");
	} else {
		ql_dbg(ql_dbg_init, vha, 0x00d3,
		    "Init Firmware -- success.\n");
		QLA_FW_STARTED(ha);
		vha->u_ql2xexchoffld = vha->u_ql2xiniexchg = 0;
	}

	return (rval);
}