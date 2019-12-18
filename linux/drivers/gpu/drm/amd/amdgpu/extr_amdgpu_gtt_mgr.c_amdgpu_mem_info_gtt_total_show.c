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
struct drm_device {struct amdgpu_device* dev_private; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_5__ {TYPE_1__* man; } ;
struct TYPE_6__ {TYPE_2__ bdev; } ;
struct amdgpu_device {TYPE_3__ mman; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {int size; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 size_t TTM_PL_TT ; 
 struct drm_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static ssize_t amdgpu_mem_info_gtt_total_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct drm_device *ddev = dev_get_drvdata(dev);
	struct amdgpu_device *adev = ddev->dev_private;

	return snprintf(buf, PAGE_SIZE, "%llu\n",
			(adev->mman.bdev.man[TTM_PL_TT].size) * PAGE_SIZE);
}