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
struct qed_iwarp_ep {int /*<<< orphan*/  cb_context; int /*<<< orphan*/  (* event_cb ) (int /*<<< orphan*/ ,struct qed_iwarp_cm_event_params*) ;int /*<<< orphan*/  cm_info; int /*<<< orphan*/  cid; } ;
struct qed_iwarp_cm_event_params {int /*<<< orphan*/ * cm_info; struct qed_iwarp_ep* ep_context; void* event; int /*<<< orphan*/  status; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  ECONNRESET ; 
#define  IWARP_EXCEPTION_DETECTED_CQ_OVERFLOW 138 
#define  IWARP_EXCEPTION_DETECTED_IRQ_FULL 137 
#define  IWARP_EXCEPTION_DETECTED_LLP_CLOSED 136 
#define  IWARP_EXCEPTION_DETECTED_LLP_RESET 135 
#define  IWARP_EXCEPTION_DETECTED_LLP_TIMEOUT 134 
#define  IWARP_EXCEPTION_DETECTED_LOCAL_ACCESS_ERROR 133 
#define  IWARP_EXCEPTION_DETECTED_LOCAL_CATASTROPHIC 132 
#define  IWARP_EXCEPTION_DETECTED_REMOTE_OPERATION_ERROR 131 
#define  IWARP_EXCEPTION_DETECTED_REMOTE_PROTECTION_ERROR 130 
#define  IWARP_EXCEPTION_DETECTED_RQ_EMPTY 129 
#define  IWARP_EXCEPTION_DETECTED_TERMINATE_RECEIVED 128 
 void* QED_IWARP_EVENT_CQ_OVERFLOW ; 
 void* QED_IWARP_EVENT_DISCONNECT ; 
 void* QED_IWARP_EVENT_IRQ_FULL ; 
 void* QED_IWARP_EVENT_LLP_TIMEOUT ; 
 void* QED_IWARP_EVENT_LOCAL_ACCESS_ERROR ; 
 void* QED_IWARP_EVENT_QP_CATASTROPHIC ; 
 void* QED_IWARP_EVENT_REMOTE_OPERATION_ERROR ; 
 void* QED_IWARP_EVENT_REMOTE_PROTECTION_ERROR ; 
 void* QED_IWARP_EVENT_RQ_EMPTY ; 
 void* QED_IWARP_EVENT_TERMINATE_RECEIVED ; 
 int /*<<< orphan*/  QED_MSG_RDMA ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct qed_iwarp_cm_event_params*) ; 

__attribute__((used)) static void qed_iwarp_exception_received(struct qed_hwfn *p_hwfn,
					 struct qed_iwarp_ep *ep,
					 int fw_ret_code)
{
	struct qed_iwarp_cm_event_params params;
	bool event_cb = false;

	DP_VERBOSE(p_hwfn, QED_MSG_RDMA, "EP(0x%x) fw_ret_code=%d\n",
		   ep->cid, fw_ret_code);

	switch (fw_ret_code) {
	case IWARP_EXCEPTION_DETECTED_LLP_CLOSED:
		params.status = 0;
		params.event = QED_IWARP_EVENT_DISCONNECT;
		event_cb = true;
		break;
	case IWARP_EXCEPTION_DETECTED_LLP_RESET:
		params.status = -ECONNRESET;
		params.event = QED_IWARP_EVENT_DISCONNECT;
		event_cb = true;
		break;
	case IWARP_EXCEPTION_DETECTED_RQ_EMPTY:
		params.event = QED_IWARP_EVENT_RQ_EMPTY;
		event_cb = true;
		break;
	case IWARP_EXCEPTION_DETECTED_IRQ_FULL:
		params.event = QED_IWARP_EVENT_IRQ_FULL;
		event_cb = true;
		break;
	case IWARP_EXCEPTION_DETECTED_LLP_TIMEOUT:
		params.event = QED_IWARP_EVENT_LLP_TIMEOUT;
		event_cb = true;
		break;
	case IWARP_EXCEPTION_DETECTED_REMOTE_PROTECTION_ERROR:
		params.event = QED_IWARP_EVENT_REMOTE_PROTECTION_ERROR;
		event_cb = true;
		break;
	case IWARP_EXCEPTION_DETECTED_CQ_OVERFLOW:
		params.event = QED_IWARP_EVENT_CQ_OVERFLOW;
		event_cb = true;
		break;
	case IWARP_EXCEPTION_DETECTED_LOCAL_CATASTROPHIC:
		params.event = QED_IWARP_EVENT_QP_CATASTROPHIC;
		event_cb = true;
		break;
	case IWARP_EXCEPTION_DETECTED_LOCAL_ACCESS_ERROR:
		params.event = QED_IWARP_EVENT_LOCAL_ACCESS_ERROR;
		event_cb = true;
		break;
	case IWARP_EXCEPTION_DETECTED_REMOTE_OPERATION_ERROR:
		params.event = QED_IWARP_EVENT_REMOTE_OPERATION_ERROR;
		event_cb = true;
		break;
	case IWARP_EXCEPTION_DETECTED_TERMINATE_RECEIVED:
		params.event = QED_IWARP_EVENT_TERMINATE_RECEIVED;
		event_cb = true;
		break;
	default:
		DP_VERBOSE(p_hwfn, QED_MSG_RDMA,
			   "Unhandled exception received...fw_ret_code=%d\n",
			   fw_ret_code);
		break;
	}

	if (event_cb) {
		params.ep_context = ep;
		params.cm_info = &ep->cm_info;
		ep->event_cb(ep->cb_context, &params);
	}
}