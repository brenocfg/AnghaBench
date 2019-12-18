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
typedef  int /*<<< orphan*/  u32 ;
struct __vxge_hw_vpath_handle {int /*<<< orphan*/  vpath; } ;
typedef  enum vxge_hw_status { ____Placeholder_vxge_hw_status } vxge_hw_status ;

/* Variables and functions */
 int VXGE_HW_ERR_INVALID_HANDLE ; 
 int VXGE_HW_OK ; 
 int __vxge_hw_vpath_alarm_process (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

enum vxge_hw_status vxge_hw_vpath_alarm_process(
			struct __vxge_hw_vpath_handle *vp,
			u32 skip_alarms)
{
	enum vxge_hw_status status = VXGE_HW_OK;

	if (vp == NULL) {
		status = VXGE_HW_ERR_INVALID_HANDLE;
		goto exit;
	}

	status = __vxge_hw_vpath_alarm_process(vp->vpath, skip_alarms);
exit:
	return status;
}