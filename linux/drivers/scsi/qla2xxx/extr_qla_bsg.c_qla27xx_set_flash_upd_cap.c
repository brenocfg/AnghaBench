#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct qla_hw_data {scalar_t__ fw_attributes; scalar_t__ fw_attributes_h; scalar_t__* fw_attributes_ext; } ;
struct qla_flash_update_caps {int capabilities; scalar_t__ outage_duration; } ;
struct TYPE_7__ {void** vendor_rsp; } ;
struct TYPE_8__ {TYPE_2__ vendor_reply; } ;
struct fc_bsg_reply {int result; scalar_t__ reply_payload_rcv_len; TYPE_3__ reply_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  sg_cnt; int /*<<< orphan*/  sg_list; } ;
struct bsg_job {int reply_len; TYPE_1__ request_payload; struct fc_bsg_reply* reply; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_9__ {struct qla_hw_data* hw; } ;
typedef  TYPE_4__ scsi_qla_host_t ;
typedef  int /*<<< orphan*/  cap ;

/* Variables and functions */
 int DID_OK ; 
 int EINVAL ; 
 int EPERM ; 
 void* EXT_STATUS_INVALID_PARAM ; 
 void* EXT_STATUS_OK ; 
 int /*<<< orphan*/  IS_QLA27XX (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_QLA28XX (struct qla_hw_data*) ; 
 scalar_t__ MAX_LOOP_TIMEOUT ; 
 int /*<<< orphan*/  bsg_job_done (struct bsg_job*,int,scalar_t__) ; 
 struct Scsi_Host* fc_bsg_to_shost (struct bsg_job*) ; 
 int /*<<< orphan*/  memset (struct qla_flash_update_caps*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_copy_to_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qla_flash_update_caps*,int) ; 
 TYPE_4__* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static int
qla27xx_set_flash_upd_cap(struct bsg_job *bsg_job)
{
	struct fc_bsg_reply *bsg_reply = bsg_job->reply;
	struct Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qla_host_t *vha = shost_priv(host);
	struct qla_hw_data *ha = vha->hw;
	uint64_t online_fw_attr = 0;
	struct qla_flash_update_caps cap;

	if (!IS_QLA27XX(ha) && !IS_QLA28XX(ha))
		return -EPERM;

	memset(&cap, 0, sizeof(cap));
	sg_copy_to_buffer(bsg_job->request_payload.sg_list,
	    bsg_job->request_payload.sg_cnt, &cap, sizeof(cap));

	online_fw_attr = (uint64_t)ha->fw_attributes_ext[1] << 48 |
			 (uint64_t)ha->fw_attributes_ext[0] << 32 |
			 (uint64_t)ha->fw_attributes_h << 16 |
			 (uint64_t)ha->fw_attributes;

	if (online_fw_attr != cap.capabilities) {
		bsg_reply->reply_data.vendor_reply.vendor_rsp[0] =
		    EXT_STATUS_INVALID_PARAM;
		return -EINVAL;
	}

	if (cap.outage_duration < MAX_LOOP_TIMEOUT)  {
		bsg_reply->reply_data.vendor_reply.vendor_rsp[0] =
		    EXT_STATUS_INVALID_PARAM;
		return -EINVAL;
	}

	bsg_reply->reply_payload_rcv_len = 0;

	bsg_reply->reply_data.vendor_reply.vendor_rsp[0] =
	    EXT_STATUS_OK;

	bsg_job->reply_len = sizeof(struct fc_bsg_reply);
	bsg_reply->result = DID_OK << 16;
	bsg_job_done(bsg_job, bsg_reply->result,
		       bsg_reply->reply_payload_rcv_len);
	return 0;
}