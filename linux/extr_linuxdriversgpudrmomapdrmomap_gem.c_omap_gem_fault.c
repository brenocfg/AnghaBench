#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_fault {struct vm_area_struct* vma; } ;
struct vm_area_struct {struct drm_gem_object* vm_private_data; } ;
struct omap_gem_object {int flags; int /*<<< orphan*/  lock; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 int OMAP_BO_TILED ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int omap_gem_attach_pages (struct drm_gem_object*) ; 
 int /*<<< orphan*/  omap_gem_fault_1d (struct drm_gem_object*,struct vm_area_struct*,struct vm_fault*) ; 
 int /*<<< orphan*/  omap_gem_fault_2d (struct drm_gem_object*,struct vm_area_struct*,struct vm_fault*) ; 
 struct omap_gem_object* to_omap_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  vmf_error (int) ; 

vm_fault_t omap_gem_fault(struct vm_fault *vmf)
{
	struct vm_area_struct *vma = vmf->vma;
	struct drm_gem_object *obj = vma->vm_private_data;
	struct omap_gem_object *omap_obj = to_omap_bo(obj);
	int err;
	vm_fault_t ret;

	/* Make sure we don't parallel update on a fault, nor move or remove
	 * something from beneath our feet
	 */
	mutex_lock(&omap_obj->lock);

	/* if a shmem backed object, make sure we have pages attached now */
	err = omap_gem_attach_pages(obj);
	if (err) {
		ret = vmf_error(err);
		goto fail;
	}

	/* where should we do corresponding put_pages().. we are mapping
	 * the original page, rather than thru a GART, so we can't rely
	 * on eviction to trigger this.  But munmap() or all mappings should
	 * probably trigger put_pages()?
	 */

	if (omap_obj->flags & OMAP_BO_TILED)
		ret = omap_gem_fault_2d(obj, vma, vmf);
	else
		ret = omap_gem_fault_1d(obj, vma, vmf);


fail:
	mutex_unlock(&omap_obj->lock);
	return ret;
}