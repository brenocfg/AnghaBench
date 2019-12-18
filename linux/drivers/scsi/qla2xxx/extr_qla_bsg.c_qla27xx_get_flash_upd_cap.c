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
struct qla_flash_update_caps {int capabilities; } ;
struct TYPE_7__ {int /*<<< orphan*/ * vendor_rsp; } ;
struct TYPE_8__ {TYPE_2__ vendor_reply; } ;
struct fc_bsg_reply {int reply_payload_rcv_len; int result; TYPE_3__ reply_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  sg_cnt; int /*<<< orphan*/  sg_list; } ;
struct bsg_job {int reply_len; TYPE_1__ reply_payload; struct fc_bsg_reply* reply; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_9__ {struct qla_hw_data* hw; } ;
typedef  TYPE_4__ scsi_qla_host_t ;
typedef  int /*<<< orphan*/  cap ;

/* Variables and functions */
 int DID_OK ; 
 int EPERM ; 
 int /*<<< orphan*/  EXT_STATUS_OK ; 
 int /*<<< orphan*/  IS_QLA27XX (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_QLA28XX (struct qla_hw_data*) ; 
 int /*<<< orphan*/  bsg_job_done (struct bsg_job*,int,int) ; 
 struct Scsi_Host* fc_bsg_to_shost (struct bsg_job*) ; 
 int /*<<< orphan*/  memset (struct qla_flash_update_caps*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_copy_from_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qla_flash_update_caps*,int) ; 
 TYPE_4__* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static int
qla27xx_get_flash_upd_cap(struct bsg_job *bsg_job)
{
	struct fc_bsg_reply *bsg_reply = bsg_job->reply;
	struct Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qla_host_t *vha = shost_priv(host);
	struct qla_hw_data *ha = vha->hw;
	struct qla_flash_update_caps cap;

	if (!(IS_QLA27XX(ha)) && !IS_QLA28XX(ha))
		return -EPERM;

	memset(&cap, 0, sizeof(cap));
	cap.capabilities = (uint64_t)ha->fw_attributes_ext[1] << 48 |
			   (uint64_t)ha->fw_attributes_ext[0] << 32 |
			   (uint64_t)ha->fw_attributes_h << 16 |
			   (uint64_t)ha->fw_attributes;

	sg_copy_from_buffer(bsg_job->reply_payload.sg_list,
	    bsg_job->reply_payload.sg_cnt, &cap, sizeof(cap));
	bsg_reply->reply_payload_rcv_len = sizeof(cap);

	bsg_reply->reply_data.vendor_reply.vendor_rsp[0] =
	    EXT_STATUS_OK;

	bsg_job->reply_len = sizeof(struct fc_bsg_reply);
	bsg_reply->result = DID_OK << 16;
	bsg_job_done(bsg_job, bsg_reply->result,
		       bsg_reply->reply_payload_rcv_len);
	return 0;
}