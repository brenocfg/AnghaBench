#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  size_t u32 ;
struct TYPE_3__ {scalar_t__ intr_mode; } ;
struct __vxge_hw_device {int vpaths_deployed; int* tim_int_mask0; size_t* tim_int_mask1; TYPE_2__* common_reg; TYPE_1__ config; int /*<<< orphan*/ * virtual_paths; } ;
struct TYPE_4__ {int /*<<< orphan*/  titan_general_int_status; int /*<<< orphan*/  tim_int_mask1; int /*<<< orphan*/  tim_int_status1; int /*<<< orphan*/  tim_int_mask0; int /*<<< orphan*/  tim_int_status0; } ;

/* Variables and functions */
 scalar_t__ VXGE_HW_INTR_MODE_IRQLINE ; 
 size_t VXGE_HW_MAX_VIRTUAL_PATHS ; 
 int /*<<< orphan*/  VXGE_HW_VIRTUAL_PATH_HANDLE (int /*<<< orphan*/ *) ; 
 size_t VXGE_HW_VPATH_INTR_RX ; 
 size_t VXGE_HW_VPATH_INTR_TX ; 
 int /*<<< orphan*/  __vxge_hw_pio_mem_write32_upper (size_t,int /*<<< orphan*/ *) ; 
 int readq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vxge_hw_device_mask_all (struct __vxge_hw_device*) ; 
 int /*<<< orphan*/  vxge_hw_device_unmask_all (struct __vxge_hw_device*) ; 
 int /*<<< orphan*/  vxge_hw_vpath_intr_enable (int /*<<< orphan*/ ) ; 
 int vxge_mBIT (size_t) ; 
 int /*<<< orphan*/  writeq (int,int /*<<< orphan*/ *) ; 

void vxge_hw_device_intr_enable(struct __vxge_hw_device *hldev)
{
	u32 i;
	u64 val64;
	u32 val32;

	vxge_hw_device_mask_all(hldev);

	for (i = 0; i < VXGE_HW_MAX_VIRTUAL_PATHS; i++) {

		if (!(hldev->vpaths_deployed & vxge_mBIT(i)))
			continue;

		vxge_hw_vpath_intr_enable(
			VXGE_HW_VIRTUAL_PATH_HANDLE(&hldev->virtual_paths[i]));
	}

	if (hldev->config.intr_mode == VXGE_HW_INTR_MODE_IRQLINE) {
		val64 = hldev->tim_int_mask0[VXGE_HW_VPATH_INTR_TX] |
			hldev->tim_int_mask0[VXGE_HW_VPATH_INTR_RX];

		if (val64 != 0) {
			writeq(val64, &hldev->common_reg->tim_int_status0);

			writeq(~val64, &hldev->common_reg->tim_int_mask0);
		}

		val32 = hldev->tim_int_mask1[VXGE_HW_VPATH_INTR_TX] |
			hldev->tim_int_mask1[VXGE_HW_VPATH_INTR_RX];

		if (val32 != 0) {
			__vxge_hw_pio_mem_write32_upper(val32,
					&hldev->common_reg->tim_int_status1);

			__vxge_hw_pio_mem_write32_upper(~val32,
					&hldev->common_reg->tim_int_mask1);
		}
	}

	val64 = readq(&hldev->common_reg->titan_general_int_status);

	vxge_hw_device_unmask_all(hldev);
}