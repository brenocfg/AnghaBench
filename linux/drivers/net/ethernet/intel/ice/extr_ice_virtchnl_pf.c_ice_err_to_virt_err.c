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
typedef  enum virtchnl_status_code { ____Placeholder_virtchnl_status_code } virtchnl_status_code ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
#define  ICE_ERR_AQ_EMPTY 142 
#define  ICE_ERR_AQ_ERROR 141 
#define  ICE_ERR_AQ_FULL 140 
#define  ICE_ERR_AQ_NO_WORK 139 
#define  ICE_ERR_AQ_TIMEOUT 138 
#define  ICE_ERR_BAD_PTR 137 
#define  ICE_ERR_CFG 136 
#define  ICE_ERR_DEVICE_NOT_SUPPORTED 135 
#define  ICE_ERR_FW_API_VER 134 
#define  ICE_ERR_INVAL_SIZE 133 
#define  ICE_ERR_NOT_READY 132 
#define  ICE_ERR_NO_MEMORY 131 
#define  ICE_ERR_PARAM 130 
#define  ICE_ERR_RESET_FAILED 129 
#define  ICE_SUCCESS 128 
 int VIRTCHNL_STATUS_ERR_ADMIN_QUEUE_ERROR ; 
 int VIRTCHNL_STATUS_ERR_NOT_SUPPORTED ; 
 int VIRTCHNL_STATUS_ERR_NO_MEMORY ; 
 int VIRTCHNL_STATUS_ERR_PARAM ; 
 int VIRTCHNL_STATUS_SUCCESS ; 

__attribute__((used)) static enum virtchnl_status_code ice_err_to_virt_err(enum ice_status ice_err)
{
	switch (ice_err) {
	case ICE_SUCCESS:
		return VIRTCHNL_STATUS_SUCCESS;
	case ICE_ERR_BAD_PTR:
	case ICE_ERR_INVAL_SIZE:
	case ICE_ERR_DEVICE_NOT_SUPPORTED:
	case ICE_ERR_PARAM:
	case ICE_ERR_CFG:
		return VIRTCHNL_STATUS_ERR_PARAM;
	case ICE_ERR_NO_MEMORY:
		return VIRTCHNL_STATUS_ERR_NO_MEMORY;
	case ICE_ERR_NOT_READY:
	case ICE_ERR_RESET_FAILED:
	case ICE_ERR_FW_API_VER:
	case ICE_ERR_AQ_ERROR:
	case ICE_ERR_AQ_TIMEOUT:
	case ICE_ERR_AQ_FULL:
	case ICE_ERR_AQ_NO_WORK:
	case ICE_ERR_AQ_EMPTY:
		return VIRTCHNL_STATUS_ERR_ADMIN_QUEUE_ERROR;
	default:
		return VIRTCHNL_STATUS_ERR_NOT_SUPPORTED;
	}
}