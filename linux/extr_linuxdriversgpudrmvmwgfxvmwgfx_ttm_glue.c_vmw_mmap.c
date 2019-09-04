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
struct vmw_private {int /*<<< orphan*/  bdev; } ;
struct vm_area_struct {scalar_t__ vm_pgoff; } ;
struct file {struct drm_file* private_data; } ;
struct drm_file {TYPE_1__* minor; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 scalar_t__ VMWGFX_FILE_PAGE_OFFSET ; 
 int ttm_bo_mmap (struct file*,struct vm_area_struct*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 struct vmw_private* vmw_priv (int /*<<< orphan*/ ) ; 

int vmw_mmap(struct file *filp, struct vm_area_struct *vma)
{
	struct drm_file *file_priv;
	struct vmw_private *dev_priv;

	if (unlikely(vma->vm_pgoff < VMWGFX_FILE_PAGE_OFFSET)) {
		DRM_ERROR("Illegal attempt to mmap old fifo space.\n");
		return -EINVAL;
	}

	file_priv = filp->private_data;
	dev_priv = vmw_priv(file_priv->minor->dev);
	return ttm_bo_mmap(filp, vma, &dev_priv->bdev);
}