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
struct __vxge_hw_device {scalar_t__ link_state; TYPE_1__* uld_callbacks; } ;
typedef  enum vxge_hw_status { ____Placeholder_vxge_hw_status } vxge_hw_status ;
struct TYPE_2__ {int /*<<< orphan*/  (* link_down ) (struct __vxge_hw_device*) ;} ;

/* Variables and functions */
 scalar_t__ VXGE_HW_LINK_DOWN ; 
 int VXGE_HW_OK ; 
 int /*<<< orphan*/  stub1 (struct __vxge_hw_device*) ; 

__attribute__((used)) static enum vxge_hw_status
__vxge_hw_device_handle_link_down_ind(struct __vxge_hw_device *hldev)
{
	/*
	 * If the previous link state is not down, return.
	 */
	if (hldev->link_state == VXGE_HW_LINK_DOWN)
		goto exit;

	hldev->link_state = VXGE_HW_LINK_DOWN;

	/* notify driver */
	if (hldev->uld_callbacks->link_down)
		hldev->uld_callbacks->link_down(hldev);
exit:
	return VXGE_HW_OK;
}