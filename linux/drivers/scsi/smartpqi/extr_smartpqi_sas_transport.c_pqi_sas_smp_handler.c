#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ device_type; } ;
struct sas_rphy {TYPE_1__ identify; } ;
struct pqi_raid_error_info {int dummy; } ;
struct pqi_ctrl_info {int dummy; } ;
struct TYPE_6__ {scalar_t__ payload_len; int sg_cnt; } ;
struct TYPE_5__ {int sg_cnt; } ;
struct bsg_job {TYPE_3__ reply_payload; TYPE_2__ request_payload; } ;
struct bmic_csmi_smp_passthru_buffer {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 scalar_t__ SAS_FANOUT_EXPANDER_DEVICE ; 
 int /*<<< orphan*/  bsg_job_done (struct bsg_job*,int,unsigned int) ; 
 struct bmic_csmi_smp_passthru_buffer* pqi_build_csmi_smp_passthru_buffer (struct sas_rphy*,struct bsg_job*) ; 
 unsigned int pqi_build_sas_smp_handler_reply (struct bmic_csmi_smp_passthru_buffer*,struct bsg_job*,struct pqi_raid_error_info*) ; 
 int pqi_csmi_smp_passthru (struct pqi_ctrl_info*,struct bmic_csmi_smp_passthru_buffer*,int,struct pqi_raid_error_info*) ; 
 scalar_t__ pqi_ctrl_blocked (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_ctrl_busy (struct pqi_ctrl_info*) ; 
 scalar_t__ pqi_ctrl_offline (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_ctrl_unbusy (struct pqi_ctrl_info*) ; 
 struct pqi_ctrl_info* shost_to_hba (struct Scsi_Host*) ; 

void pqi_sas_smp_handler(struct bsg_job *job, struct Scsi_Host *shost,
	struct sas_rphy *rphy)
{
	int rc;
	struct pqi_ctrl_info *ctrl_info = shost_to_hba(shost);
	struct bmic_csmi_smp_passthru_buffer *smp_buf;
	struct pqi_raid_error_info error_info;
	unsigned int reslen = 0;

	pqi_ctrl_busy(ctrl_info);

	if (job->reply_payload.payload_len == 0) {
		rc = -ENOMEM;
		goto out;
	}

	if (!rphy) {
		rc = -EINVAL;
		goto out;
	}

	if (rphy->identify.device_type != SAS_FANOUT_EXPANDER_DEVICE) {
		rc = -EINVAL;
		goto out;
	}

	if (job->request_payload.sg_cnt > 1 || job->reply_payload.sg_cnt > 1) {
		rc = -EINVAL;
		goto out;
	}

	if (pqi_ctrl_offline(ctrl_info)) {
		rc = -ENXIO;
		goto out;
	}

	if (pqi_ctrl_blocked(ctrl_info)) {
		rc = -EBUSY;
		goto out;
	}

	smp_buf = pqi_build_csmi_smp_passthru_buffer(rphy, job);
	if (!smp_buf) {
		rc = -ENOMEM;
		goto out;
	}

	rc = pqi_csmi_smp_passthru(ctrl_info, smp_buf, sizeof(*smp_buf),
		&error_info);
	if (rc)
		goto out;

	reslen = pqi_build_sas_smp_handler_reply(smp_buf, job, &error_info);
out:
	bsg_job_done(job, rc, reslen);
	pqi_ctrl_unbusy(ctrl_info);
}