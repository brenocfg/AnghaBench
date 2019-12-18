#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct lpfc_trunk_info {int port_speed; int logical_speed; } ;
struct TYPE_17__ {int speed; int logical_speed; } ;
struct TYPE_18__ {TYPE_8__ link_state; } ;
struct TYPE_15__ {scalar_t__ state; } ;
struct TYPE_14__ {scalar_t__ state; } ;
struct TYPE_13__ {scalar_t__ state; } ;
struct TYPE_12__ {scalar_t__ state; } ;
struct TYPE_16__ {TYPE_6__ link3; TYPE_5__ link2; TYPE_4__ link1; TYPE_3__ link0; } ;
struct lpfc_hba {scalar_t__ link_state; TYPE_9__ sli4_hba; TYPE_7__ trunk_link; } ;
struct get_trunk_info_req {int dummy; } ;
struct fc_bsg_request {int dummy; } ;
struct TYPE_10__ {scalar_t__ vendor_rsp; } ;
struct TYPE_11__ {TYPE_1__ vendor_reply; } ;
struct fc_bsg_reply {int result; int /*<<< orphan*/  reply_payload_rcv_len; TYPE_2__ reply_data; } ;
struct bsg_job {int request_len; int reply_len; struct fc_bsg_reply* reply; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  LOG_LIBDFC ; 
 scalar_t__ LPFC_LINK_UP ; 
 int bf_get (int /*<<< orphan*/ ,TYPE_9__*) ; 
 int /*<<< orphan*/  bsg_bf_set (int /*<<< orphan*/ ,struct lpfc_trunk_info*,int) ; 
 int /*<<< orphan*/  bsg_job_done (struct bsg_job*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_bsg_to_shost (struct bsg_job*) ; 
 int /*<<< orphan*/  lpfc_conf_trunk_port0 ; 
 int /*<<< orphan*/  lpfc_conf_trunk_port1 ; 
 int /*<<< orphan*/  lpfc_conf_trunk_port2 ; 
 int /*<<< orphan*/  lpfc_conf_trunk_port3 ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lpfc_trunk_info_link_status ; 
 int /*<<< orphan*/  lpfc_trunk_info_trunk_active0 ; 
 int /*<<< orphan*/  lpfc_trunk_info_trunk_active1 ; 
 int /*<<< orphan*/  lpfc_trunk_info_trunk_active2 ; 
 int /*<<< orphan*/  lpfc_trunk_info_trunk_active3 ; 
 int /*<<< orphan*/  lpfc_trunk_info_trunk_config0 ; 
 int /*<<< orphan*/  lpfc_trunk_info_trunk_config1 ; 
 int /*<<< orphan*/  lpfc_trunk_info_trunk_config2 ; 
 int /*<<< orphan*/  lpfc_trunk_info_trunk_config3 ; 
 struct lpfc_vport* shost_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpfc_get_trunk_info(struct bsg_job *job)
{
	struct lpfc_vport *vport = shost_priv(fc_bsg_to_shost(job));
	struct lpfc_hba *phba = vport->phba;
	struct fc_bsg_reply *bsg_reply = job->reply;
	struct lpfc_trunk_info *event_reply;
	int rc = 0;

	if (job->request_len <
	    sizeof(struct fc_bsg_request) + sizeof(struct get_trunk_info_req)) {
		lpfc_printf_log(phba, KERN_ERR, LOG_LIBDFC,
				"2744 Received GET TRUNK _INFO request below "
				"minimum size\n");
		rc = -EINVAL;
		goto job_error;
	}

	event_reply = (struct lpfc_trunk_info *)
		bsg_reply->reply_data.vendor_reply.vendor_rsp;

	if (job->reply_len <
	    sizeof(struct fc_bsg_request) + sizeof(struct lpfc_trunk_info)) {
		lpfc_printf_log(phba, KERN_WARNING, LOG_LIBDFC,
				"2728 Received GET TRUNK _INFO reply below "
				"minimum size\n");
		rc = -EINVAL;
		goto job_error;
	}
	if (event_reply == NULL) {
		rc = -EINVAL;
		goto job_error;
	}

	bsg_bf_set(lpfc_trunk_info_link_status, event_reply,
		   (phba->link_state >= LPFC_LINK_UP) ? 1 : 0);

	bsg_bf_set(lpfc_trunk_info_trunk_active0, event_reply,
		   (phba->trunk_link.link0.state == LPFC_LINK_UP) ? 1 : 0);

	bsg_bf_set(lpfc_trunk_info_trunk_active1, event_reply,
		   (phba->trunk_link.link1.state == LPFC_LINK_UP) ? 1 : 0);

	bsg_bf_set(lpfc_trunk_info_trunk_active2, event_reply,
		   (phba->trunk_link.link2.state == LPFC_LINK_UP) ? 1 : 0);

	bsg_bf_set(lpfc_trunk_info_trunk_active3, event_reply,
		   (phba->trunk_link.link3.state == LPFC_LINK_UP) ? 1 : 0);

	bsg_bf_set(lpfc_trunk_info_trunk_config0, event_reply,
		   bf_get(lpfc_conf_trunk_port0, &phba->sli4_hba));

	bsg_bf_set(lpfc_trunk_info_trunk_config1, event_reply,
		   bf_get(lpfc_conf_trunk_port1, &phba->sli4_hba));

	bsg_bf_set(lpfc_trunk_info_trunk_config2, event_reply,
		   bf_get(lpfc_conf_trunk_port2, &phba->sli4_hba));

	bsg_bf_set(lpfc_trunk_info_trunk_config3, event_reply,
		   bf_get(lpfc_conf_trunk_port3, &phba->sli4_hba));

	event_reply->port_speed = phba->sli4_hba.link_state.speed / 1000;
	event_reply->logical_speed =
				phba->sli4_hba.link_state.logical_speed / 1000;
job_error:
	bsg_reply->result = rc;
	if (!rc)
		bsg_job_done(job, bsg_reply->result,
			     bsg_reply->reply_payload_rcv_len);
	return rc;

}