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
struct qedi_endpoint {int /*<<< orphan*/  handle; } ;
struct qedi_ctx {int /*<<< orphan*/  dbg_ctx; int /*<<< orphan*/  cdev; } ;
struct qedi_conn {struct qedi_endpoint* ep; struct iscsi_cls_conn* cls_conn; } ;
struct qed_iscsi_params_update {int /*<<< orphan*/  exp_stat_sn; int /*<<< orphan*/  first_seq_length; int /*<<< orphan*/  max_send_pdu_length; int /*<<< orphan*/  max_recv_pdu_length; int /*<<< orphan*/  max_seq_size; scalar_t__ update_flag; } ;
struct iscsi_conn {int /*<<< orphan*/  exp_statsn; TYPE_1__* session; int /*<<< orphan*/  max_xmit_dlength; int /*<<< orphan*/  max_recv_dlength; scalar_t__ datadgst_en; scalar_t__ hdrdgst_en; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;
struct TYPE_4__ {int (* update_conn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qed_iscsi_params_update*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  first_burst; int /*<<< orphan*/  max_burst; scalar_t__ imm_data_en; scalar_t__ initial_r2t_en; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ISCSI_CONN_UPDATE_RAMROD_PARAMS_DD_EN ; 
 int /*<<< orphan*/  ISCSI_CONN_UPDATE_RAMROD_PARAMS_HD_EN ; 
 int /*<<< orphan*/  ISCSI_CONN_UPDATE_RAMROD_PARAMS_IMMEDIATE_DATA ; 
 int /*<<< orphan*/  ISCSI_CONN_UPDATE_RAMROD_PARAMS_INITIAL_R2T ; 
 int /*<<< orphan*/  QEDI_ERR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SET_FIELD (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct qed_iscsi_params_update*) ; 
 struct qed_iscsi_params_update* kzalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_2__* qedi_ops ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qed_iscsi_params_update*) ; 

__attribute__((used)) static int qedi_iscsi_update_conn(struct qedi_ctx *qedi,
				  struct qedi_conn *qedi_conn)
{
	struct qed_iscsi_params_update *conn_info;
	struct iscsi_cls_conn *cls_conn = qedi_conn->cls_conn;
	struct iscsi_conn *conn = cls_conn->dd_data;
	struct qedi_endpoint *qedi_ep;
	int rval;

	qedi_ep = qedi_conn->ep;

	conn_info = kzalloc(sizeof(*conn_info), GFP_KERNEL);
	if (!conn_info) {
		QEDI_ERR(&qedi->dbg_ctx, "memory alloc failed\n");
		return -ENOMEM;
	}

	conn_info->update_flag = 0;

	if (conn->hdrdgst_en)
		SET_FIELD(conn_info->update_flag,
			  ISCSI_CONN_UPDATE_RAMROD_PARAMS_HD_EN, true);
	if (conn->datadgst_en)
		SET_FIELD(conn_info->update_flag,
			  ISCSI_CONN_UPDATE_RAMROD_PARAMS_DD_EN, true);
	if (conn->session->initial_r2t_en)
		SET_FIELD(conn_info->update_flag,
			  ISCSI_CONN_UPDATE_RAMROD_PARAMS_INITIAL_R2T,
			  true);
	if (conn->session->imm_data_en)
		SET_FIELD(conn_info->update_flag,
			  ISCSI_CONN_UPDATE_RAMROD_PARAMS_IMMEDIATE_DATA,
			  true);

	conn_info->max_seq_size = conn->session->max_burst;
	conn_info->max_recv_pdu_length = conn->max_recv_dlength;
	conn_info->max_send_pdu_length = conn->max_xmit_dlength;
	conn_info->first_seq_length = conn->session->first_burst;
	conn_info->exp_stat_sn = conn->exp_statsn;

	rval = qedi_ops->update_conn(qedi->cdev, qedi_ep->handle,
				     conn_info);
	if (rval) {
		rval = -ENXIO;
		QEDI_ERR(&qedi->dbg_ctx, "Could not update connection\n");
	}

	kfree(conn_info);
	return rval;
}