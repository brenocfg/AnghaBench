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
struct zfcp_fsf_req {int status; TYPE_2__* qtcb; struct zfcp_fsf_ct_els* data; } ;
struct zfcp_fsf_ct_els {int /*<<< orphan*/  handler_data; int /*<<< orphan*/  (* handler ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  status; } ;
struct TYPE_3__ {int /*<<< orphan*/ * word; } ;
struct fsf_qtcb_header {int fsf_status; TYPE_1__ fsf_status_qual; } ;
struct TYPE_4__ {struct fsf_qtcb_header header; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
#define  FSF_ADAPTER_STATUS_AVAILABLE 138 
#define  FSF_ELS_COMMAND_REJECTED 137 
#define  FSF_GOOD 136 
#define  FSF_PAYLOAD_SIZE_MISMATCH 135 
#define  FSF_REQUEST_SIZE_TOO_LARGE 134 
#define  FSF_RESPONSE_SIZE_TOO_LARGE 133 
#define  FSF_SBAL_MISMATCH 132 
#define  FSF_SERVICE_CLASS_NOT_SUPPORTED 131 
#define  FSF_SQ_INVOKE_LINK_TEST_PROCEDURE 130 
#define  FSF_SQ_RETRY_IF_POSSIBLE 129 
#define  FSF_SQ_ULP_DEPENDENT_ERP_REQUIRED 128 
 int ZFCP_STATUS_FSFREQ_ERROR ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_dbf_san_res (char*,struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_fsf_class_not_supp (struct zfcp_fsf_req*) ; 

__attribute__((used)) static void zfcp_fsf_send_els_handler(struct zfcp_fsf_req *req)
{
	struct zfcp_fsf_ct_els *send_els = req->data;
	struct fsf_qtcb_header *header = &req->qtcb->header;

	send_els->status = -EINVAL;

	if (req->status & ZFCP_STATUS_FSFREQ_ERROR)
		goto skip_fsfstatus;

	switch (header->fsf_status) {
	case FSF_GOOD:
		send_els->status = 0;
		zfcp_dbf_san_res("fsselh1", req);
		break;
	case FSF_SERVICE_CLASS_NOT_SUPPORTED:
		zfcp_fsf_class_not_supp(req);
		break;
	case FSF_ADAPTER_STATUS_AVAILABLE:
		switch (header->fsf_status_qual.word[0]){
		case FSF_SQ_INVOKE_LINK_TEST_PROCEDURE:
		case FSF_SQ_ULP_DEPENDENT_ERP_REQUIRED:
		case FSF_SQ_RETRY_IF_POSSIBLE:
			req->status |= ZFCP_STATUS_FSFREQ_ERROR;
			break;
		}
		break;
	case FSF_ELS_COMMAND_REJECTED:
	case FSF_PAYLOAD_SIZE_MISMATCH:
	case FSF_REQUEST_SIZE_TOO_LARGE:
	case FSF_RESPONSE_SIZE_TOO_LARGE:
		break;
	case FSF_SBAL_MISMATCH:
		/* should never occur, avoided in zfcp_fsf_send_els */
		/* fall through */
	default:
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		break;
	}
skip_fsfstatus:
	if (send_els->handler)
		send_els->handler(send_els->handler_data);
}