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
struct dmcu_iram_parameters {int backlight_ramping_start; int backlight_ramping_reduction; int backlight_lut_array_size; unsigned int* backlight_lut_array; scalar_t__ set; } ;
struct dmcu {int dummy; } ;
struct TYPE_6__ {TYPE_2__* dc; } ;
struct amdgpu_device {scalar_t__ asic_type; int /*<<< orphan*/  ddev; TYPE_3__ dm; } ;
struct TYPE_5__ {TYPE_1__* res_pool; } ;
struct TYPE_4__ {struct dmcu* dmcu; } ;

/* Variables and functions */
 scalar_t__ CHIP_RAVEN ; 
 int EINVAL ; 
 int detect_mst_link_for_all_connectors (int /*<<< orphan*/ ) ; 
 int dmcu_load_iram (struct dmcu*,struct dmcu_iram_parameters) ; 

__attribute__((used)) static int dm_late_init(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	struct dmcu_iram_parameters params;
	unsigned int linear_lut[16];
	int i;
	struct dmcu *dmcu = adev->dm.dc->res_pool->dmcu;
	bool ret = false;

	for (i = 0; i < 16; i++)
		linear_lut[i] = 0xFFFF * i / 15;

	params.set = 0;
	params.backlight_ramping_start = 0xCCCC;
	params.backlight_ramping_reduction = 0xCCCCCCCC;
	params.backlight_lut_array_size = 16;
	params.backlight_lut_array = linear_lut;

	/* todo will enable for navi10 */
	if (adev->asic_type <= CHIP_RAVEN) {
		ret = dmcu_load_iram(dmcu, params);

		if (!ret)
			return -EINVAL;
	}

	return detect_mst_link_for_all_connectors(adev->ddev);
}