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
typedef  int uint ;
struct TYPE_4__ {TYPE_1__* instance; } ;
struct amdgpu_device {int asic_type; TYPE_2__ sdma; } ;
struct TYPE_3__ {int fw_version; } ;

/* Variables and functions */
#define  CHIP_VEGA10 130 
#define  CHIP_VEGA12 129 
#define  CHIP_VEGA20 128 

__attribute__((used)) static bool sdma_v4_0_fw_support_paging_queue(struct amdgpu_device *adev)
{
	uint fw_version = adev->sdma.instance[0].fw_version;

	switch (adev->asic_type) {
	case CHIP_VEGA10:
		return fw_version >= 430;
	case CHIP_VEGA12:
		/*return fw_version >= 31;*/
		return false;
	case CHIP_VEGA20:
		return fw_version >= 123;
	default:
		return false;
	}
}