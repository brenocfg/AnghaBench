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
struct __vxge_hw_device {int vpaths_deployed; } ;

/* Variables and functions */
 int VXGE_HW_MAX_POLLING_COUNT ; 
 int VXGE_HW_MAX_VIRTUAL_PATHS ; 
 scalar_t__ vxge_hw_vpath_wait_receive_idle (struct __vxge_hw_device*,int) ; 
 int vxge_mBIT (int) ; 

void vxge_hw_device_wait_receive_idle(struct __vxge_hw_device *hldev)
{
	int i, total_count = 0;

	for (i = 0; i < VXGE_HW_MAX_VIRTUAL_PATHS; i++) {
		if (!(hldev->vpaths_deployed & vxge_mBIT(i)))
			continue;

		total_count += vxge_hw_vpath_wait_receive_idle(hldev, i);
		if (total_count >= VXGE_HW_MAX_POLLING_COUNT)
			break;
	}
}