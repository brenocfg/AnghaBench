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
struct creq_func_event {int event; } ;
struct bnxt_qplib_rcfw {int dummy; } ;

/* Variables and functions */
#define  CREQ_FUNC_EVENT_EVENT_CFCC_ERROR 140 
#define  CREQ_FUNC_EVENT_EVENT_CFCM_ERROR 139 
#define  CREQ_FUNC_EVENT_EVENT_CFCQ_ERROR 138 
#define  CREQ_FUNC_EVENT_EVENT_CFCS_ERROR 137 
#define  CREQ_FUNC_EVENT_EVENT_CQ_ERROR 136 
#define  CREQ_FUNC_EVENT_EVENT_RESOURCE_EXHAUSTED 135 
#define  CREQ_FUNC_EVENT_EVENT_RX_DATA_ERROR 134 
#define  CREQ_FUNC_EVENT_EVENT_RX_WQE_ERROR 133 
#define  CREQ_FUNC_EVENT_EVENT_TIM_ERROR 132 
#define  CREQ_FUNC_EVENT_EVENT_TQM_ERROR 131 
#define  CREQ_FUNC_EVENT_EVENT_TX_DATA_ERROR 130 
#define  CREQ_FUNC_EVENT_EVENT_TX_WQE_ERROR 129 
#define  CREQ_FUNC_EVENT_EVENT_VF_COMM_REQUEST 128 
 int EINVAL ; 

__attribute__((used)) static int bnxt_qplib_process_func_event(struct bnxt_qplib_rcfw *rcfw,
					 struct creq_func_event *func_event)
{
	switch (func_event->event) {
	case CREQ_FUNC_EVENT_EVENT_TX_WQE_ERROR:
		break;
	case CREQ_FUNC_EVENT_EVENT_TX_DATA_ERROR:
		break;
	case CREQ_FUNC_EVENT_EVENT_RX_WQE_ERROR:
		break;
	case CREQ_FUNC_EVENT_EVENT_RX_DATA_ERROR:
		break;
	case CREQ_FUNC_EVENT_EVENT_CQ_ERROR:
		break;
	case CREQ_FUNC_EVENT_EVENT_TQM_ERROR:
		break;
	case CREQ_FUNC_EVENT_EVENT_CFCQ_ERROR:
		break;
	case CREQ_FUNC_EVENT_EVENT_CFCS_ERROR:
		/* SRQ ctx error, call srq_handler??
		 * But there's no SRQ handle!
		 */
		break;
	case CREQ_FUNC_EVENT_EVENT_CFCC_ERROR:
		break;
	case CREQ_FUNC_EVENT_EVENT_CFCM_ERROR:
		break;
	case CREQ_FUNC_EVENT_EVENT_TIM_ERROR:
		break;
	case CREQ_FUNC_EVENT_EVENT_VF_COMM_REQUEST:
		break;
	case CREQ_FUNC_EVENT_EVENT_RESOURCE_EXHAUSTED:
		break;
	default:
		return -EINVAL;
	}
	return 0;
}