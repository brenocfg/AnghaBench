#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  handle; } ;
struct TYPE_12__ {int domain_flags; int bo_size; int domains; int /*<<< orphan*/  alignment; } ;
union drm_amdgpu_gem_create {TYPE_6__ out; TYPE_3__ in; } ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u32 ;
struct drm_gem_object {int dummy; } ;
struct drm_file {struct amdgpu_fpriv* driver_priv; } ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct dma_resv {int dummy; } ;
struct TYPE_13__ {TYPE_7__* bo; } ;
struct TYPE_14__ {TYPE_4__ base; } ;
struct amdgpu_vm {TYPE_5__ root; } ;
struct amdgpu_fpriv {struct amdgpu_vm vm; } ;
struct amdgpu_device {int dummy; } ;
struct amdgpu_bo {int /*<<< orphan*/  parent; } ;
struct TYPE_10__ {struct dma_resv* resv; } ;
struct TYPE_11__ {TYPE_1__ base; } ;
struct TYPE_16__ {TYPE_2__ tbo; } ;

/* Variables and functions */
 int AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED ; 
 int AMDGPU_GEM_CREATE_CPU_GTT_USWC ; 
 int AMDGPU_GEM_CREATE_EXPLICIT_SYNC ; 
 int AMDGPU_GEM_CREATE_NO_CPU_ACCESS ; 
 int AMDGPU_GEM_CREATE_VM_ALWAYS_VALID ; 
 int AMDGPU_GEM_CREATE_VRAM_CLEARED ; 
 int AMDGPU_GEM_DOMAIN_GDS ; 
 int AMDGPU_GEM_DOMAIN_GWS ; 
 int AMDGPU_GEM_DOMAIN_MASK ; 
 int AMDGPU_GEM_DOMAIN_OA ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  amdgpu_bo_ref (TYPE_7__*) ; 
 int amdgpu_bo_reserve (TYPE_7__*,int) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (TYPE_7__*) ; 
 int amdgpu_gem_object_create (struct amdgpu_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct dma_resv*,struct drm_gem_object**) ; 
 int drm_gem_handle_create (struct drm_file*,struct drm_gem_object*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 struct amdgpu_bo* gem_to_amdgpu_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  memset (union drm_amdgpu_gem_create*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ttm_bo_type_device ; 

int amdgpu_gem_create_ioctl(struct drm_device *dev, void *data,
			    struct drm_file *filp)
{
	struct amdgpu_device *adev = dev->dev_private;
	struct amdgpu_fpriv *fpriv = filp->driver_priv;
	struct amdgpu_vm *vm = &fpriv->vm;
	union drm_amdgpu_gem_create *args = data;
	uint64_t flags = args->in.domain_flags;
	uint64_t size = args->in.bo_size;
	struct dma_resv *resv = NULL;
	struct drm_gem_object *gobj;
	uint32_t handle;
	int r;

	/* reject invalid gem flags */
	if (flags & ~(AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED |
		      AMDGPU_GEM_CREATE_NO_CPU_ACCESS |
		      AMDGPU_GEM_CREATE_CPU_GTT_USWC |
		      AMDGPU_GEM_CREATE_VRAM_CLEARED |
		      AMDGPU_GEM_CREATE_VM_ALWAYS_VALID |
		      AMDGPU_GEM_CREATE_EXPLICIT_SYNC))

		return -EINVAL;

	/* reject invalid gem domains */
	if (args->in.domains & ~AMDGPU_GEM_DOMAIN_MASK)
		return -EINVAL;

	/* create a gem object to contain this object in */
	if (args->in.domains & (AMDGPU_GEM_DOMAIN_GDS |
	    AMDGPU_GEM_DOMAIN_GWS | AMDGPU_GEM_DOMAIN_OA)) {
		if (flags & AMDGPU_GEM_CREATE_VM_ALWAYS_VALID) {
			/* if gds bo is created from user space, it must be
			 * passed to bo list
			 */
			DRM_ERROR("GDS bo cannot be per-vm-bo\n");
			return -EINVAL;
		}
		flags |= AMDGPU_GEM_CREATE_NO_CPU_ACCESS;
	}

	if (flags & AMDGPU_GEM_CREATE_VM_ALWAYS_VALID) {
		r = amdgpu_bo_reserve(vm->root.base.bo, false);
		if (r)
			return r;

		resv = vm->root.base.bo->tbo.base.resv;
	}

	r = amdgpu_gem_object_create(adev, size, args->in.alignment,
				     (u32)(0xffffffff & args->in.domains),
				     flags, ttm_bo_type_device, resv, &gobj);
	if (flags & AMDGPU_GEM_CREATE_VM_ALWAYS_VALID) {
		if (!r) {
			struct amdgpu_bo *abo = gem_to_amdgpu_bo(gobj);

			abo->parent = amdgpu_bo_ref(vm->root.base.bo);
		}
		amdgpu_bo_unreserve(vm->root.base.bo);
	}
	if (r)
		return r;

	r = drm_gem_handle_create(filp, gobj, &handle);
	/* drop reference from allocate - handle holds it now */
	drm_gem_object_put_unlocked(gobj);
	if (r)
		return r;

	memset(args, 0, sizeof(*args));
	args->out.handle = handle;
	return 0;
}