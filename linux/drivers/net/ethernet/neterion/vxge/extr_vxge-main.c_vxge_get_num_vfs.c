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
typedef  int u64 ;
typedef  int u32 ;

/* Variables and functions */
#define  VXGE_HW_FUNCTION_MODE_MRIOV 136 
#define  VXGE_HW_FUNCTION_MODE_MRIOV_8 135 
#define  VXGE_HW_FUNCTION_MODE_MULTI_FUNCTION 134 
#define  VXGE_HW_FUNCTION_MODE_MULTI_FUNCTION_17 133 
#define  VXGE_HW_FUNCTION_MODE_MULTI_FUNCTION_2 132 
#define  VXGE_HW_FUNCTION_MODE_SINGLE_FUNCTION 131 
#define  VXGE_HW_FUNCTION_MODE_SRIOV 130 
#define  VXGE_HW_FUNCTION_MODE_SRIOV_4 129 
#define  VXGE_HW_FUNCTION_MODE_SRIOV_8 128 

__attribute__((used)) static inline u32 vxge_get_num_vfs(u64 function_mode)
{
	u32 num_functions = 0;

	switch (function_mode) {
	case VXGE_HW_FUNCTION_MODE_MULTI_FUNCTION:
	case VXGE_HW_FUNCTION_MODE_SRIOV_8:
		num_functions = 8;
		break;
	case VXGE_HW_FUNCTION_MODE_SINGLE_FUNCTION:
		num_functions = 1;
		break;
	case VXGE_HW_FUNCTION_MODE_SRIOV:
	case VXGE_HW_FUNCTION_MODE_MRIOV:
	case VXGE_HW_FUNCTION_MODE_MULTI_FUNCTION_17:
		num_functions = 17;
		break;
	case VXGE_HW_FUNCTION_MODE_SRIOV_4:
		num_functions = 4;
		break;
	case VXGE_HW_FUNCTION_MODE_MULTI_FUNCTION_2:
		num_functions = 2;
		break;
	case VXGE_HW_FUNCTION_MODE_MRIOV_8:
		num_functions = 8; /* TODO */
		break;
	}
	return num_functions;
}