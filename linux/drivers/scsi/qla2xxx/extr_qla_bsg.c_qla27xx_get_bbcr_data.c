#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct qla_hw_data {int dummy; } ;
struct qla_bbcr_data {scalar_t__ status; int negotiated_bbscn; int configured_bbscn; void* state; int /*<<< orphan*/  offline_reason_code; int /*<<< orphan*/  mbx1; } ;
struct TYPE_10__ {int /*<<< orphan*/ * vendor_rsp; } ;
struct TYPE_11__ {TYPE_3__ vendor_reply; } ;
struct fc_bsg_reply {int reply_payload_rcv_len; int result; TYPE_4__ reply_data; } ;
struct TYPE_9__ {int /*<<< orphan*/  sg_cnt; int /*<<< orphan*/  sg_list; } ;
struct bsg_job {int reply_len; TYPE_2__ reply_payload; struct fc_bsg_reply* reply; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_8__ {scalar_t__ bbcr_enable; } ;
struct TYPE_12__ {int bbcr; TYPE_1__ flags; struct qla_hw_data* hw; } ;
typedef  TYPE_5__ scsi_qla_host_t ;
typedef  int /*<<< orphan*/  bbcr ;

/* Variables and functions */
 int DID_OK ; 
 int EPERM ; 
 int /*<<< orphan*/  EXT_STATUS_OK ; 
 int /*<<< orphan*/  IS_QLA27XX (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_QLA28XX (struct qla_hw_data*) ; 
 int /*<<< orphan*/  QLA_BBCR_REASON_LOGIN_REJECT ; 
 void* QLA_BBCR_STATE_OFFLINE ; 
 void* QLA_BBCR_STATE_ONLINE ; 
 scalar_t__ QLA_BBCR_STATUS_DISABLED ; 
 scalar_t__ QLA_BBCR_STATUS_ENABLED ; 
 scalar_t__ QLA_BBCR_STATUS_UNKNOWN ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  bsg_job_done (struct bsg_job*,int,int) ; 
 struct Scsi_Host* fc_bsg_to_shost (struct bsg_job*) ; 
 int /*<<< orphan*/  memset (struct qla_bbcr_data*,int /*<<< orphan*/ ,int) ; 
 int qla2x00_get_adapter_id (TYPE_5__*,int /*<<< orphan*/ *,int*,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_copy_from_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qla_bbcr_data*,int) ; 
 TYPE_5__* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static int
qla27xx_get_bbcr_data(struct bsg_job *bsg_job)
{
	struct fc_bsg_reply *bsg_reply = bsg_job->reply;
	struct Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qla_host_t *vha = shost_priv(host);
	struct qla_hw_data *ha = vha->hw;
	struct qla_bbcr_data bbcr;
	uint16_t loop_id, topo, sw_cap;
	uint8_t domain, area, al_pa, state;
	int rval;

	if (!IS_QLA27XX(ha) && !IS_QLA28XX(ha))
		return -EPERM;

	memset(&bbcr, 0, sizeof(bbcr));

	if (vha->flags.bbcr_enable)
		bbcr.status = QLA_BBCR_STATUS_ENABLED;
	else
		bbcr.status = QLA_BBCR_STATUS_DISABLED;

	if (bbcr.status == QLA_BBCR_STATUS_ENABLED) {
		rval = qla2x00_get_adapter_id(vha, &loop_id, &al_pa,
			&area, &domain, &topo, &sw_cap);
		if (rval != QLA_SUCCESS) {
			bbcr.status = QLA_BBCR_STATUS_UNKNOWN;
			bbcr.state = QLA_BBCR_STATE_OFFLINE;
			bbcr.mbx1 = loop_id;
			goto done;
		}

		state = (vha->bbcr >> 12) & 0x1;

		if (state) {
			bbcr.state = QLA_BBCR_STATE_OFFLINE;
			bbcr.offline_reason_code = QLA_BBCR_REASON_LOGIN_REJECT;
		} else {
			bbcr.state = QLA_BBCR_STATE_ONLINE;
			bbcr.negotiated_bbscn = (vha->bbcr >> 8) & 0xf;
		}

		bbcr.configured_bbscn = vha->bbcr & 0xf;
	}

done:
	sg_copy_from_buffer(bsg_job->reply_payload.sg_list,
		bsg_job->reply_payload.sg_cnt, &bbcr, sizeof(bbcr));
	bsg_reply->reply_payload_rcv_len = sizeof(bbcr);

	bsg_reply->reply_data.vendor_reply.vendor_rsp[0] = EXT_STATUS_OK;

	bsg_job->reply_len = sizeof(struct fc_bsg_reply);
	bsg_reply->result = DID_OK << 16;
	bsg_job_done(bsg_job, bsg_reply->result,
		       bsg_reply->reply_payload_rcv_len);
	return 0;
}