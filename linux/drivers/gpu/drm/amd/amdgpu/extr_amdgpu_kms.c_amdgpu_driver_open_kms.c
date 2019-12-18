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
typedef  int uint64_t ;
struct drm_file {struct amdgpu_fpriv* driver_priv; } ;
struct drm_device {int /*<<< orphan*/  dev; struct amdgpu_device* dev_private; } ;
struct amdgpu_fpriv {int /*<<< orphan*/  vm; int /*<<< orphan*/  ctx_mgr; int /*<<< orphan*/  bo_list_handles; int /*<<< orphan*/  bo_list_lock; int /*<<< orphan*/  csa_va; int /*<<< orphan*/  prt_va; } ;
struct TYPE_2__ {int /*<<< orphan*/  csa_obj; } ;
struct amdgpu_device {TYPE_1__ virt; int /*<<< orphan*/  dev; int /*<<< orphan*/  delayed_init_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_CSA_SIZE ; 
 int AMDGPU_GMC_HOLE_MASK ; 
 int /*<<< orphan*/  AMDGPU_VM_CONTEXT_GFX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int amdgpu_csa_vaddr (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_ctx_mgr_init (int /*<<< orphan*/ *) ; 
 int amdgpu_map_static_csa (struct amdgpu_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ amdgpu_mcbp ; 
 int amdgpu_pasid_alloc (int) ; 
 int /*<<< orphan*/  amdgpu_pasid_free (int) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_vm_bo_add (struct amdgpu_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_vm_fini (struct amdgpu_device*,int /*<<< orphan*/ *) ; 
 int amdgpu_vm_init (struct amdgpu_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  flush_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct amdgpu_fpriv*) ; 
 struct amdgpu_fpriv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int amdgpu_driver_open_kms(struct drm_device *dev, struct drm_file *file_priv)
{
	struct amdgpu_device *adev = dev->dev_private;
	struct amdgpu_fpriv *fpriv;
	int r, pasid;

	/* Ensure IB tests are run on ring */
	flush_delayed_work(&adev->delayed_init_work);

	file_priv->driver_priv = NULL;

	r = pm_runtime_get_sync(dev->dev);
	if (r < 0)
		return r;

	fpriv = kzalloc(sizeof(*fpriv), GFP_KERNEL);
	if (unlikely(!fpriv)) {
		r = -ENOMEM;
		goto out_suspend;
	}

	pasid = amdgpu_pasid_alloc(16);
	if (pasid < 0) {
		dev_warn(adev->dev, "No more PASIDs available!");
		pasid = 0;
	}
	r = amdgpu_vm_init(adev, &fpriv->vm, AMDGPU_VM_CONTEXT_GFX, pasid);
	if (r)
		goto error_pasid;

	fpriv->prt_va = amdgpu_vm_bo_add(adev, &fpriv->vm, NULL);
	if (!fpriv->prt_va) {
		r = -ENOMEM;
		goto error_vm;
	}

	if (amdgpu_mcbp || amdgpu_sriov_vf(adev)) {
		uint64_t csa_addr = amdgpu_csa_vaddr(adev) & AMDGPU_GMC_HOLE_MASK;

		r = amdgpu_map_static_csa(adev, &fpriv->vm, adev->virt.csa_obj,
						&fpriv->csa_va, csa_addr, AMDGPU_CSA_SIZE);
		if (r)
			goto error_vm;
	}

	mutex_init(&fpriv->bo_list_lock);
	idr_init(&fpriv->bo_list_handles);

	amdgpu_ctx_mgr_init(&fpriv->ctx_mgr);

	file_priv->driver_priv = fpriv;
	goto out_suspend;

error_vm:
	amdgpu_vm_fini(adev, &fpriv->vm);

error_pasid:
	if (pasid)
		amdgpu_pasid_free(pasid);

	kfree(fpriv);

out_suspend:
	pm_runtime_mark_last_busy(dev->dev);
	pm_runtime_put_autosuspend(dev->dev);

	return r;
}