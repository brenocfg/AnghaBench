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
struct vm_area_struct {int dummy; } ;
struct file {struct drm_file* private_data; } ;
struct drm_file {TYPE_2__* minor; } ;
struct TYPE_6__ {int /*<<< orphan*/  bdev; } ;
struct amdgpu_device {TYPE_3__ mman; } ;
struct TYPE_5__ {TYPE_1__* dev; } ;
struct TYPE_4__ {struct amdgpu_device* dev_private; } ;

/* Variables and functions */
 int EINVAL ; 
 int ttm_bo_mmap (struct file*,struct vm_area_struct*,int /*<<< orphan*/ *) ; 

int amdgpu_mmap(struct file *filp, struct vm_area_struct *vma)
{
	struct drm_file *file_priv = filp->private_data;
	struct amdgpu_device *adev = file_priv->minor->dev->dev_private;

	if (adev == NULL)
		return -EINVAL;

	return ttm_bo_mmap(filp, vma, &adev->mman.bdev);
}