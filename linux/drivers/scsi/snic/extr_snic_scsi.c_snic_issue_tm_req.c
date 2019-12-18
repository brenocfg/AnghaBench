#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snic_req_info {int dummy; } ;
struct snic_host_req {int dummy; } ;
struct snic {int /*<<< orphan*/  ios_inflight; int /*<<< orphan*/  shost; } ;
struct scsi_cmnd {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int SCSI_NO_TAG ; 
 scalar_t__ SNIC_FWRESET ; 
 int /*<<< orphan*/  SNIC_HOST_ERR (int /*<<< orphan*/ ,char*,int,struct scsi_cmnd*,struct snic_req_info*,int,int,int) ; 
 int SNIC_ITMF_LUN_RESET ; 
 int /*<<< orphan*/  SNIC_SCSI_DBG (int /*<<< orphan*/ ,char*,int,struct scsi_cmnd*,int,...) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct snic_host_req* snic_abort_req_init (struct snic*,struct snic_req_info*) ; 
 int snic_cmd_tag (struct scsi_cmnd*) ; 
 struct snic_host_req* snic_dr_req_init (struct snic*,struct snic_req_info*) ; 
 scalar_t__ snic_get_state (struct snic*) ; 
 int snic_queue_itmf_req (struct snic*,struct snic_host_req*,struct scsi_cmnd*,int,int) ; 

__attribute__((used)) static int
snic_issue_tm_req(struct snic *snic,
		    struct snic_req_info *rqi,
		    struct scsi_cmnd *sc,
		    int tmf)
{
	struct snic_host_req *tmreq = NULL;
	int req_id = 0, tag = snic_cmd_tag(sc);
	int ret = 0;

	if (snic_get_state(snic) == SNIC_FWRESET)
		return -EBUSY;

	atomic_inc(&snic->ios_inflight);

	SNIC_SCSI_DBG(snic->shost,
		      "issu_tmreq: Task mgmt req %d. rqi %p w/ tag %x\n",
		      tmf, rqi, tag);


	if (tmf == SNIC_ITMF_LUN_RESET) {
		tmreq = snic_dr_req_init(snic, rqi);
		req_id = SCSI_NO_TAG;
	} else {
		tmreq = snic_abort_req_init(snic, rqi);
		req_id = tag;
	}

	if (!tmreq) {
		ret = -ENOMEM;

		goto tmreq_err;
	}

	ret = snic_queue_itmf_req(snic, tmreq, sc, tmf, req_id);
	if (ret)
		goto tmreq_err;

	ret = 0;

tmreq_err:
	if (ret) {
		SNIC_HOST_ERR(snic->shost,
			      "issu_tmreq: Queing ITMF(%d) Req, sc %p rqi %p req_id %d tag %x fails err = %d\n",
			      tmf, sc, rqi, req_id, tag, ret);
	} else {
		SNIC_SCSI_DBG(snic->shost,
			      "issu_tmreq: Queuing ITMF(%d) Req, sc %p, rqi %p, req_id %d tag %x - Success.\n",
			      tmf, sc, rqi, req_id, tag);
	}

	atomic_dec(&snic->ios_inflight);

	return ret;
}