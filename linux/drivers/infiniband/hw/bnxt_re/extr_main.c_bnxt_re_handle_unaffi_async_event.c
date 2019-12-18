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

/* Variables and functions */
#define  CREQ_FUNC_EVENT_EVENT_CFCC_ERROR 138 
#define  CREQ_FUNC_EVENT_EVENT_CFCM_ERROR 137 
#define  CREQ_FUNC_EVENT_EVENT_CFCQ_ERROR 136 
#define  CREQ_FUNC_EVENT_EVENT_CFCS_ERROR 135 
#define  CREQ_FUNC_EVENT_EVENT_CQ_ERROR 134 
#define  CREQ_FUNC_EVENT_EVENT_RX_DATA_ERROR 133 
#define  CREQ_FUNC_EVENT_EVENT_RX_WQE_ERROR 132 
#define  CREQ_FUNC_EVENT_EVENT_TIM_ERROR 131 
#define  CREQ_FUNC_EVENT_EVENT_TQM_ERROR 130 
#define  CREQ_FUNC_EVENT_EVENT_TX_DATA_ERROR 129 
#define  CREQ_FUNC_EVENT_EVENT_TX_WQE_ERROR 128 
 int EINVAL ; 

__attribute__((used)) static int bnxt_re_handle_unaffi_async_event(struct creq_func_event
					     *unaffi_async)
{
	switch (unaffi_async->event) {
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
		break;
	case CREQ_FUNC_EVENT_EVENT_CFCC_ERROR:
		break;
	case CREQ_FUNC_EVENT_EVENT_CFCM_ERROR:
		break;
	case CREQ_FUNC_EVENT_EVENT_TIM_ERROR:
		break;
	default:
		return -EINVAL;
	}
	return 0;
}