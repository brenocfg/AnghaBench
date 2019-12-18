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
typedef  enum vmmdev_hgcm_function_parameter_type { ____Placeholder_vmmdev_hgcm_function_parameter_type } vmmdev_hgcm_function_parameter_type ;

/* Variables and functions */
#define  VMMDEV_HGCM_PARM_TYPE_32BIT 132 
#define  VMMDEV_HGCM_PARM_TYPE_64BIT 131 
#define  VMMDEV_HGCM_PARM_TYPE_LINADDR 130 
#define  VMMDEV_HGCM_PARM_TYPE_LINADDR_IN 129 
#define  VMMDEV_HGCM_PARM_TYPE_LINADDR_OUT 128 

__attribute__((used)) static bool vbg_param_valid(enum vmmdev_hgcm_function_parameter_type type)
{
	switch (type) {
	case VMMDEV_HGCM_PARM_TYPE_32BIT:
	case VMMDEV_HGCM_PARM_TYPE_64BIT:
	case VMMDEV_HGCM_PARM_TYPE_LINADDR:
	case VMMDEV_HGCM_PARM_TYPE_LINADDR_IN:
	case VMMDEV_HGCM_PARM_TYPE_LINADDR_OUT:
		return true;
	default:
		return false;
	}
}