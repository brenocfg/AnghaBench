#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct __vxge_hw_device {TYPE_1__* uld_callbacks; } ;
typedef  enum vxge_hw_status { ____Placeholder_vxge_hw_status } vxge_hw_status ;
typedef  enum vxge_hw_event { ____Placeholder_vxge_hw_event } vxge_hw_event ;
struct TYPE_2__ {int /*<<< orphan*/  (* crit_err ) (struct __vxge_hw_device*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
#define  VXGE_HW_EVENT_ALARM_CLEARED 142 
#define  VXGE_HW_EVENT_CRITICAL_ERR 141 
#define  VXGE_HW_EVENT_ECCERR 140 
#define  VXGE_HW_EVENT_FIFO_ERR 139 
#define  VXGE_HW_EVENT_LINK_DOWN 138 
#define  VXGE_HW_EVENT_LINK_UP 137 
#define  VXGE_HW_EVENT_MRPCIM_ECCERR 136 
#define  VXGE_HW_EVENT_MRPCIM_SERR 135 
#define  VXGE_HW_EVENT_RESET_COMPLETE 134 
#define  VXGE_HW_EVENT_RESET_START 133 
#define  VXGE_HW_EVENT_SERR 132 
#define  VXGE_HW_EVENT_SLOT_FREEZE 131 
#define  VXGE_HW_EVENT_SRPCIM_SERR 130 
#define  VXGE_HW_EVENT_UNKNOWN 129 
#define  VXGE_HW_EVENT_VPATH_ERR 128 
 int VXGE_HW_OK ; 
 int /*<<< orphan*/  stub1 (struct __vxge_hw_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxge_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum vxge_hw_status
__vxge_hw_device_handle_error(struct __vxge_hw_device *hldev, u32 vp_id,
			      enum vxge_hw_event type)
{
	switch (type) {
	case VXGE_HW_EVENT_UNKNOWN:
		break;
	case VXGE_HW_EVENT_RESET_START:
	case VXGE_HW_EVENT_RESET_COMPLETE:
	case VXGE_HW_EVENT_LINK_DOWN:
	case VXGE_HW_EVENT_LINK_UP:
		goto out;
	case VXGE_HW_EVENT_ALARM_CLEARED:
		goto out;
	case VXGE_HW_EVENT_ECCERR:
	case VXGE_HW_EVENT_MRPCIM_ECCERR:
		goto out;
	case VXGE_HW_EVENT_FIFO_ERR:
	case VXGE_HW_EVENT_VPATH_ERR:
	case VXGE_HW_EVENT_CRITICAL_ERR:
	case VXGE_HW_EVENT_SERR:
		break;
	case VXGE_HW_EVENT_SRPCIM_SERR:
	case VXGE_HW_EVENT_MRPCIM_SERR:
		goto out;
	case VXGE_HW_EVENT_SLOT_FREEZE:
		break;
	default:
		vxge_assert(0);
		goto out;
	}

	/* notify driver */
	if (hldev->uld_callbacks->crit_err)
		hldev->uld_callbacks->crit_err(hldev,
			type, vp_id);
out:

	return VXGE_HW_OK;
}