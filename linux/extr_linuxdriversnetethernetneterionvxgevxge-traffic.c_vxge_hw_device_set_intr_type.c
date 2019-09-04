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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ intr_mode; } ;
struct __vxge_hw_device {TYPE_1__ config; } ;

/* Variables and functions */
 scalar_t__ VXGE_HW_INTR_MODE_DEF ; 
 scalar_t__ VXGE_HW_INTR_MODE_IRQLINE ; 
 scalar_t__ VXGE_HW_INTR_MODE_MSIX ; 
 scalar_t__ VXGE_HW_INTR_MODE_MSIX_ONE_SHOT ; 

u32 vxge_hw_device_set_intr_type(struct __vxge_hw_device *hldev, u32 intr_mode)
{

	if ((intr_mode != VXGE_HW_INTR_MODE_IRQLINE) &&
	   (intr_mode != VXGE_HW_INTR_MODE_MSIX) &&
	   (intr_mode != VXGE_HW_INTR_MODE_MSIX_ONE_SHOT) &&
	   (intr_mode != VXGE_HW_INTR_MODE_DEF))
		intr_mode = VXGE_HW_INTR_MODE_IRQLINE;

	hldev->config.intr_mode = intr_mode;
	return intr_mode;
}