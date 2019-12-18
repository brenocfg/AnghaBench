#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct mm_struct {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {struct amdgpu_fpriv* driver_priv; } ;
struct TYPE_14__ {TYPE_5__* bo; } ;
struct TYPE_15__ {TYPE_6__ base; } ;
struct amdgpu_vm {TYPE_7__ root; } ;
struct amdgpu_fpriv {struct amdgpu_vm vm; } ;
struct amdgpu_device {int dummy; } ;
struct amdgpu_bo_va {int /*<<< orphan*/  ref_count; } ;
struct TYPE_9__ {scalar_t__ resv; } ;
struct TYPE_10__ {TYPE_1__ base; int /*<<< orphan*/  ttm; int /*<<< orphan*/  bdev; } ;
struct amdgpu_bo {int flags; TYPE_2__ tbo; } ;
struct TYPE_16__ {struct mm_struct* mm; } ;
struct TYPE_11__ {scalar_t__ resv; } ;
struct TYPE_12__ {TYPE_3__ base; } ;
struct TYPE_13__ {TYPE_4__ tbo; } ;

/* Variables and functions */
 int AMDGPU_GEM_CREATE_VM_ALWAYS_VALID ; 
 int EPERM ; 
 int amdgpu_bo_reserve (struct amdgpu_bo*,int) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (struct amdgpu_bo*) ; 
 struct amdgpu_device* amdgpu_ttm_adev (int /*<<< orphan*/ ) ; 
 struct mm_struct* amdgpu_ttm_tt_get_usermm (int /*<<< orphan*/ ) ; 
 struct amdgpu_bo_va* amdgpu_vm_bo_add (struct amdgpu_device*,struct amdgpu_vm*,struct amdgpu_bo*) ; 
 struct amdgpu_bo_va* amdgpu_vm_bo_find (struct amdgpu_vm*,struct amdgpu_bo*) ; 
 TYPE_8__* current ; 
 struct amdgpu_bo* gem_to_amdgpu_bo (struct drm_gem_object*) ; 

int amdgpu_gem_object_open(struct drm_gem_object *obj,
			   struct drm_file *file_priv)
{
	struct amdgpu_bo *abo = gem_to_amdgpu_bo(obj);
	struct amdgpu_device *adev = amdgpu_ttm_adev(abo->tbo.bdev);
	struct amdgpu_fpriv *fpriv = file_priv->driver_priv;
	struct amdgpu_vm *vm = &fpriv->vm;
	struct amdgpu_bo_va *bo_va;
	struct mm_struct *mm;
	int r;

	mm = amdgpu_ttm_tt_get_usermm(abo->tbo.ttm);
	if (mm && mm != current->mm)
		return -EPERM;

	if (abo->flags & AMDGPU_GEM_CREATE_VM_ALWAYS_VALID &&
	    abo->tbo.base.resv != vm->root.base.bo->tbo.base.resv)
		return -EPERM;

	r = amdgpu_bo_reserve(abo, false);
	if (r)
		return r;

	bo_va = amdgpu_vm_bo_find(vm, abo);
	if (!bo_va) {
		bo_va = amdgpu_vm_bo_add(adev, vm, abo);
	} else {
		++bo_va->ref_count;
	}
	amdgpu_bo_unreserve(abo);
	return 0;
}