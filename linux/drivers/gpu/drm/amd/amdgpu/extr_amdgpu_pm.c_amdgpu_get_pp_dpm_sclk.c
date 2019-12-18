#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct drm_device {struct amdgpu_device* dev_private; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_6__ {TYPE_1__* pp_funcs; } ;
struct TYPE_7__ {TYPE_4__* ops; } ;
struct amdgpu_device {TYPE_2__ powerplay; int /*<<< orphan*/  smu; TYPE_3__ virt; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* get_pp_clk ) (struct amdgpu_device*,int /*<<< orphan*/ ,char*) ;} ;
struct TYPE_5__ {scalar_t__ print_clock_levels; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PP_SCLK ; 
 int /*<<< orphan*/  SMU_SCLK ; 
 scalar_t__ amdgim_is_hwperf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_dpm_print_clock_levels (struct amdgpu_device*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 struct drm_device* dev_get_drvdata (struct device*) ; 
 scalar_t__ is_support_sw_smu (struct amdgpu_device*) ; 
 int /*<<< orphan*/  smu_print_clk_levels (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_device*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t amdgpu_get_pp_dpm_sclk(struct device *dev,
		struct device_attribute *attr,
		char *buf)
{
	struct drm_device *ddev = dev_get_drvdata(dev);
	struct amdgpu_device *adev = ddev->dev_private;

	if (amdgpu_sriov_vf(adev) && amdgim_is_hwperf(adev) &&
	    adev->virt.ops->get_pp_clk)
		return adev->virt.ops->get_pp_clk(adev, PP_SCLK, buf);

	if (is_support_sw_smu(adev))
		return smu_print_clk_levels(&adev->smu, SMU_SCLK, buf);
	else if (adev->powerplay.pp_funcs->print_clock_levels)
		return amdgpu_dpm_print_clock_levels(adev, PP_SCLK, buf);
	else
		return snprintf(buf, PAGE_SIZE, "\n");
}