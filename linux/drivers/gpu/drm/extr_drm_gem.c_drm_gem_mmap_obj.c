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
struct vm_area_struct {unsigned long vm_end; unsigned long vm_start; int vm_flags; int /*<<< orphan*/  vm_page_prot; struct drm_gem_object* vm_private_data; scalar_t__ vm_ops; } ;
struct drm_gem_object {TYPE_1__* funcs; struct drm_device* dev; } ;
struct drm_device {TYPE_2__* driver; } ;
struct TYPE_4__ {scalar_t__ gem_vm_ops; } ;
struct TYPE_3__ {scalar_t__ vm_ops; } ;

/* Variables and functions */
 int EINVAL ; 
 int VM_DONTDUMP ; 
 int VM_DONTEXPAND ; 
 int VM_IO ; 
 int VM_PFNMAP ; 
 int /*<<< orphan*/  drm_gem_object_get (struct drm_gem_object*) ; 
 int /*<<< orphan*/  pgprot_decrypted (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgprot_writecombine (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_get_page_prot (int) ; 

int drm_gem_mmap_obj(struct drm_gem_object *obj, unsigned long obj_size,
		     struct vm_area_struct *vma)
{
	struct drm_device *dev = obj->dev;

	/* Check for valid size. */
	if (obj_size < vma->vm_end - vma->vm_start)
		return -EINVAL;

	if (obj->funcs && obj->funcs->vm_ops)
		vma->vm_ops = obj->funcs->vm_ops;
	else if (dev->driver->gem_vm_ops)
		vma->vm_ops = dev->driver->gem_vm_ops;
	else
		return -EINVAL;

	vma->vm_flags |= VM_IO | VM_PFNMAP | VM_DONTEXPAND | VM_DONTDUMP;
	vma->vm_private_data = obj;
	vma->vm_page_prot = pgprot_writecombine(vm_get_page_prot(vma->vm_flags));
	vma->vm_page_prot = pgprot_decrypted(vma->vm_page_prot);

	/* Take a ref for this mapping of the object, so that the fault
	 * handler can dereference the mmap offset's pointer to the object.
	 * This reference is cleaned up by the corresponding vm_close
	 * (which should happen whether the vma was created by this call, or
	 * by a vm_open due to mremap or partial unmap or whatever).
	 */
	drm_gem_object_get(obj);

	return 0;
}