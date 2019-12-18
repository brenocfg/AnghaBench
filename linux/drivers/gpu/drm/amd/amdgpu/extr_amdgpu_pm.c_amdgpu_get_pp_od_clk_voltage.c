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
typedef  int uint32_t ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* pp_funcs; } ;
struct amdgpu_device {TYPE_2__ powerplay; int /*<<< orphan*/  smu; } ;
typedef  int ssize_t ;
struct TYPE_3__ {scalar_t__ print_clock_levels; } ;

/* Variables and functions */
 int /*<<< orphan*/  OD_MCLK ; 
 int /*<<< orphan*/  OD_RANGE ; 
 int /*<<< orphan*/  OD_SCLK ; 
 int /*<<< orphan*/  OD_VDDC_CURVE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SMU_OD_MCLK ; 
 int /*<<< orphan*/  SMU_OD_RANGE ; 
 int /*<<< orphan*/  SMU_OD_SCLK ; 
 int /*<<< orphan*/  SMU_OD_VDDC_CURVE ; 
 int amdgpu_dpm_print_clock_levels (struct amdgpu_device*,int /*<<< orphan*/ ,char*) ; 
 struct drm_device* dev_get_drvdata (struct device*) ; 
 scalar_t__ is_support_sw_smu (struct amdgpu_device*) ; 
 int smu_print_clk_levels (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t amdgpu_get_pp_od_clk_voltage(struct device *dev,
		struct device_attribute *attr,
		char *buf)
{
	struct drm_device *ddev = dev_get_drvdata(dev);
	struct amdgpu_device *adev = ddev->dev_private;
	uint32_t size = 0;

	if (is_support_sw_smu(adev)) {
		size = smu_print_clk_levels(&adev->smu, SMU_OD_SCLK, buf);
		size += smu_print_clk_levels(&adev->smu, SMU_OD_MCLK, buf+size);
		size += smu_print_clk_levels(&adev->smu, SMU_OD_VDDC_CURVE, buf+size);
		size += smu_print_clk_levels(&adev->smu, SMU_OD_RANGE, buf+size);
		return size;
	} else if (adev->powerplay.pp_funcs->print_clock_levels) {
		size = amdgpu_dpm_print_clock_levels(adev, OD_SCLK, buf);
		size += amdgpu_dpm_print_clock_levels(adev, OD_MCLK, buf+size);
		size += amdgpu_dpm_print_clock_levels(adev, OD_VDDC_CURVE, buf+size);
		size += amdgpu_dpm_print_clock_levels(adev, OD_RANGE, buf+size);
		return size;
	} else {
		return snprintf(buf, PAGE_SIZE, "\n");
	}

}