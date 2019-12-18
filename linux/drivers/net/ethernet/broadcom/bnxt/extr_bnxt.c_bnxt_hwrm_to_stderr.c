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
typedef  int u32 ;

/* Variables and functions */
 int EACCES ; 
 int EAGAIN ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int EOPNOTSUPP ; 
#define  HWRM_ERR_CODE_CMD_NOT_SUPPORTED 138 
#define  HWRM_ERR_CODE_HOT_RESET_PROGRESS 137 
#define  HWRM_ERR_CODE_INVALID_ENABLES 136 
#define  HWRM_ERR_CODE_INVALID_FLAGS 135 
#define  HWRM_ERR_CODE_INVALID_PARAMS 134 
#define  HWRM_ERR_CODE_NO_BUFFER 133 
#define  HWRM_ERR_CODE_RESOURCE_ACCESS_DENIED 132 
#define  HWRM_ERR_CODE_RESOURCE_ALLOC_ERROR 131 
#define  HWRM_ERR_CODE_SUCCESS 130 
#define  HWRM_ERR_CODE_UNSUPPORTED_OPTION_ERR 129 
#define  HWRM_ERR_CODE_UNSUPPORTED_TLV 128 

__attribute__((used)) static int bnxt_hwrm_to_stderr(u32 hwrm_err)
{
	switch (hwrm_err) {
	case HWRM_ERR_CODE_SUCCESS:
		return 0;
	case HWRM_ERR_CODE_RESOURCE_ACCESS_DENIED:
		return -EACCES;
	case HWRM_ERR_CODE_RESOURCE_ALLOC_ERROR:
		return -ENOSPC;
	case HWRM_ERR_CODE_INVALID_PARAMS:
	case HWRM_ERR_CODE_INVALID_FLAGS:
	case HWRM_ERR_CODE_INVALID_ENABLES:
	case HWRM_ERR_CODE_UNSUPPORTED_TLV:
	case HWRM_ERR_CODE_UNSUPPORTED_OPTION_ERR:
		return -EINVAL;
	case HWRM_ERR_CODE_NO_BUFFER:
		return -ENOMEM;
	case HWRM_ERR_CODE_HOT_RESET_PROGRESS:
		return -EAGAIN;
	case HWRM_ERR_CODE_CMD_NOT_SUPPORTED:
		return -EOPNOTSUPP;
	default:
		return -EIO;
	}
}