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
struct vm_area_struct {scalar_t__ vm_pgoff; int vm_flags; struct ttm_buffer_object* vm_private_data; int /*<<< orphan*/ * vm_ops; } ;
struct ttm_buffer_object {TYPE_1__* bdev; } ;
struct ttm_bo_driver {int (* verify_access ) (struct ttm_buffer_object*,struct file*) ;} ;
struct ttm_bo_device {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {struct ttm_bo_driver* driver; } ;

/* Variables and functions */
 scalar_t__ DRM_FILE_PAGE_OFFSET_START ; 
 int EINVAL ; 
 int EPERM ; 
 int VM_DONTDUMP ; 
 int VM_DONTEXPAND ; 
 int VM_IO ; 
 int VM_MIXEDMAP ; 
 int stub1 (struct ttm_buffer_object*,struct file*) ; 
 int /*<<< orphan*/  ttm_bo_put (struct ttm_buffer_object*) ; 
 struct ttm_buffer_object* ttm_bo_vm_lookup (struct ttm_bo_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_bo_vm_ops ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vma_pages (struct vm_area_struct*) ; 

int ttm_bo_mmap(struct file *filp, struct vm_area_struct *vma,
		struct ttm_bo_device *bdev)
{
	struct ttm_bo_driver *driver;
	struct ttm_buffer_object *bo;
	int ret;

	if (unlikely(vma->vm_pgoff < DRM_FILE_PAGE_OFFSET_START))
		return -EINVAL;

	bo = ttm_bo_vm_lookup(bdev, vma->vm_pgoff, vma_pages(vma));
	if (unlikely(!bo))
		return -EINVAL;

	driver = bo->bdev->driver;
	if (unlikely(!driver->verify_access)) {
		ret = -EPERM;
		goto out_unref;
	}
	ret = driver->verify_access(bo, filp);
	if (unlikely(ret != 0))
		goto out_unref;

	vma->vm_ops = &ttm_bo_vm_ops;

	/*
	 * Note: We're transferring the bo reference to
	 * vma->vm_private_data here.
	 */

	vma->vm_private_data = bo;

	/*
	 * We'd like to use VM_PFNMAP on shared mappings, where
	 * (vma->vm_flags & VM_SHARED) != 0, for performance reasons,
	 * but for some reason VM_PFNMAP + x86 PAT + write-combine is very
	 * bad for performance. Until that has been sorted out, use
	 * VM_MIXEDMAP on all mappings. See freedesktop.org bug #75719
	 */
	vma->vm_flags |= VM_MIXEDMAP;
	vma->vm_flags |= VM_IO | VM_DONTEXPAND | VM_DONTDUMP;
	return 0;
out_unref:
	ttm_bo_put(bo);
	return ret;
}