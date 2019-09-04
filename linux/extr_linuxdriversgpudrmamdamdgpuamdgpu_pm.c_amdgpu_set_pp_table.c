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
struct drm_device {struct amdgpu_device* dev_private; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* pp_funcs; } ;
struct amdgpu_device {TYPE_2__ powerplay; } ;
typedef  size_t ssize_t ;
struct TYPE_3__ {scalar_t__ set_pp_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_dpm_set_pp_table (struct amdgpu_device*,char const*,size_t) ; 
 struct drm_device* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static ssize_t amdgpu_set_pp_table(struct device *dev,
		struct device_attribute *attr,
		const char *buf,
		size_t count)
{
	struct drm_device *ddev = dev_get_drvdata(dev);
	struct amdgpu_device *adev = ddev->dev_private;

	if (adev->powerplay.pp_funcs->set_pp_table)
		amdgpu_dpm_set_pp_table(adev, buf, count);

	return count;
}