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
struct TYPE_3__ {int* vendor_cmd; } ;
struct TYPE_4__ {TYPE_1__ h_vendor; } ;
struct fc_bsg_request {TYPE_2__ rqst_data; } ;
struct fc_bsg_reply {int result; int /*<<< orphan*/  reply_payload_rcv_len; } ;
struct bsg_job {struct fc_bsg_reply* reply; struct fc_bsg_request* request; } ;

/* Variables and functions */
 int EINVAL ; 
#define  LPFC_BSG_VENDOR_DIAG_MODE 144 
#define  LPFC_BSG_VENDOR_DIAG_MODE_END 143 
#define  LPFC_BSG_VENDOR_DIAG_RUN_LOOPBACK 142 
#define  LPFC_BSG_VENDOR_FORCED_LINK_SPEED 141 
#define  LPFC_BSG_VENDOR_GET_CT_EVENT 140 
#define  LPFC_BSG_VENDOR_GET_MGMT_REV 139 
#define  LPFC_BSG_VENDOR_GET_TRUNK_INFO 138 
#define  LPFC_BSG_VENDOR_LINK_DIAG_TEST 137 
#define  LPFC_BSG_VENDOR_MBOX 136 
#define  LPFC_BSG_VENDOR_MENLO_CMD 135 
#define  LPFC_BSG_VENDOR_MENLO_DATA 134 
#define  LPFC_BSG_VENDOR_RAS_GET_CONFIG 133 
#define  LPFC_BSG_VENDOR_RAS_GET_FWLOG 132 
#define  LPFC_BSG_VENDOR_RAS_GET_LWPD 131 
#define  LPFC_BSG_VENDOR_RAS_SET_CONFIG 130 
#define  LPFC_BSG_VENDOR_SEND_MGMT_RESP 129 
#define  LPFC_BSG_VENDOR_SET_CT_EVENT 128 
 int lpfc_bsg_diag_loopback_mode (struct bsg_job*) ; 
 int lpfc_bsg_diag_loopback_run (struct bsg_job*) ; 
 int lpfc_bsg_get_dfc_rev (struct bsg_job*) ; 
 int lpfc_bsg_get_ras_config (struct bsg_job*) ; 
 int lpfc_bsg_get_ras_fwlog (struct bsg_job*) ; 
 int lpfc_bsg_get_ras_lwpd (struct bsg_job*) ; 
 int lpfc_bsg_hba_get_event (struct bsg_job*) ; 
 int lpfc_bsg_hba_set_event (struct bsg_job*) ; 
 int lpfc_bsg_mbox_cmd (struct bsg_job*) ; 
 int lpfc_bsg_send_mgmt_rsp (struct bsg_job*) ; 
 int lpfc_bsg_set_ras_config (struct bsg_job*) ; 
 int lpfc_forced_link_speed (struct bsg_job*) ; 
 int lpfc_get_trunk_info (struct bsg_job*) ; 
 int lpfc_menlo_cmd (struct bsg_job*) ; 
 int lpfc_sli4_bsg_diag_mode_end (struct bsg_job*) ; 
 int lpfc_sli4_bsg_link_diag_test (struct bsg_job*) ; 

__attribute__((used)) static int
lpfc_bsg_hst_vendor(struct bsg_job *job)
{
	struct fc_bsg_request *bsg_request = job->request;
	struct fc_bsg_reply *bsg_reply = job->reply;
	int command = bsg_request->rqst_data.h_vendor.vendor_cmd[0];
	int rc;

	switch (command) {
	case LPFC_BSG_VENDOR_SET_CT_EVENT:
		rc = lpfc_bsg_hba_set_event(job);
		break;
	case LPFC_BSG_VENDOR_GET_CT_EVENT:
		rc = lpfc_bsg_hba_get_event(job);
		break;
	case LPFC_BSG_VENDOR_SEND_MGMT_RESP:
		rc = lpfc_bsg_send_mgmt_rsp(job);
		break;
	case LPFC_BSG_VENDOR_DIAG_MODE:
		rc = lpfc_bsg_diag_loopback_mode(job);
		break;
	case LPFC_BSG_VENDOR_DIAG_MODE_END:
		rc = lpfc_sli4_bsg_diag_mode_end(job);
		break;
	case LPFC_BSG_VENDOR_DIAG_RUN_LOOPBACK:
		rc = lpfc_bsg_diag_loopback_run(job);
		break;
	case LPFC_BSG_VENDOR_LINK_DIAG_TEST:
		rc = lpfc_sli4_bsg_link_diag_test(job);
		break;
	case LPFC_BSG_VENDOR_GET_MGMT_REV:
		rc = lpfc_bsg_get_dfc_rev(job);
		break;
	case LPFC_BSG_VENDOR_MBOX:
		rc = lpfc_bsg_mbox_cmd(job);
		break;
	case LPFC_BSG_VENDOR_MENLO_CMD:
	case LPFC_BSG_VENDOR_MENLO_DATA:
		rc = lpfc_menlo_cmd(job);
		break;
	case LPFC_BSG_VENDOR_FORCED_LINK_SPEED:
		rc = lpfc_forced_link_speed(job);
		break;
	case LPFC_BSG_VENDOR_RAS_GET_LWPD:
		rc = lpfc_bsg_get_ras_lwpd(job);
		break;
	case LPFC_BSG_VENDOR_RAS_GET_FWLOG:
		rc = lpfc_bsg_get_ras_fwlog(job);
		break;
	case LPFC_BSG_VENDOR_RAS_GET_CONFIG:
		rc = lpfc_bsg_get_ras_config(job);
		break;
	case LPFC_BSG_VENDOR_RAS_SET_CONFIG:
		rc = lpfc_bsg_set_ras_config(job);
		break;
	case LPFC_BSG_VENDOR_GET_TRUNK_INFO:
		rc = lpfc_get_trunk_info(job);
		break;
	default:
		rc = -EINVAL;
		bsg_reply->reply_payload_rcv_len = 0;
		/* make error code available to userspace */
		bsg_reply->result = rc;
		break;
	}

	return rc;
}