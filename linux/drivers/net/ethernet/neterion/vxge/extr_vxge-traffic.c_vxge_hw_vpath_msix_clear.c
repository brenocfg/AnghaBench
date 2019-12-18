#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct __vxge_hw_vpath_handle {TYPE_2__* vpath; } ;
struct TYPE_6__ {scalar_t__ intr_mode; } ;
struct __vxge_hw_device {TYPE_1__* common_reg; TYPE_3__ config; } ;
struct TYPE_5__ {struct __vxge_hw_device* hldev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * clear_msix_mask_vect; int /*<<< orphan*/ * clr_msix_one_shot_vec; } ;

/* Variables and functions */
 scalar_t__ VXGE_HW_INTR_MODE_MSIX_ONE_SHOT ; 
 int /*<<< orphan*/  __vxge_hw_pio_mem_write32_upper (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ vxge_bVALn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vxge_mBIT (int) ; 

void vxge_hw_vpath_msix_clear(struct __vxge_hw_vpath_handle *vp, int msix_id)
{
	struct __vxge_hw_device *hldev = vp->vpath->hldev;

	if (hldev->config.intr_mode == VXGE_HW_INTR_MODE_MSIX_ONE_SHOT)
		__vxge_hw_pio_mem_write32_upper(
			(u32) vxge_bVALn(vxge_mBIT((msix_id >> 2)), 0, 32),
			&hldev->common_reg->clr_msix_one_shot_vec[msix_id % 4]);
	else
		__vxge_hw_pio_mem_write32_upper(
			(u32) vxge_bVALn(vxge_mBIT((msix_id >> 2)), 0, 32),
			&hldev->common_reg->clear_msix_mask_vect[msix_id % 4]);
}