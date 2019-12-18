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
struct vc4_bo {scalar_t__ madv; int /*<<< orphan*/  madv_lock; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_FAULT_SIGBUS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ __VC4_MADV_PURGED ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct vc4_bo* to_vc4_bo (struct drm_gem_object*) ; 

vm_fault_t vc4_fault(struct vm_fault *vmf)
{
	struct vm_area_struct *vma = vmf->vma;
	struct drm_gem_object *obj = vma->vm_private_data;
	struct vc4_bo *bo = to_vc4_bo(obj);

	/* The only reason we would end up here is when user-space accesses
	 * BO's memory after it's been purged.
	 */
	mutex_lock(&bo->madv_lock);
	WARN_ON(bo->madv != __VC4_MADV_PURGED);
	mutex_unlock(&bo->madv_lock);

	return VM_FAULT_SIGBUS;
}