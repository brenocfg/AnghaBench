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
struct ras_manager {int dummy; } ;
struct amdgpu_ras {int /*<<< orphan*/  supported; int /*<<< orphan*/  hw_supported; int /*<<< orphan*/  flags; int /*<<< orphan*/  head; scalar_t__ features; struct ras_manager* objs; } ;
struct TYPE_4__ {TYPE_1__* funcs; } ;
struct amdgpu_device {TYPE_2__ umc; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* ras_init ) (struct amdgpu_device*) ;} ;

/* Variables and functions */
 int AMDGPU_RAS_BLOCK_COUNT ; 
 int /*<<< orphan*/  AMDGPU_RAS_BLOCK_MASK ; 
 int /*<<< orphan*/  DRM_INFO (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RAS_DEFAULT_FLAGS ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  amdgpu_ras_check_supported (struct amdgpu_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ amdgpu_ras_fs_init (struct amdgpu_device*) ; 
 struct amdgpu_ras* amdgpu_ras_get_context (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_ras_mask ; 
 int /*<<< orphan*/  amdgpu_ras_recovery_fini (struct amdgpu_device*) ; 
 scalar_t__ amdgpu_ras_recovery_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_ras_set_context (struct amdgpu_device*,struct amdgpu_ras*) ; 
 int /*<<< orphan*/  kfree (struct amdgpu_ras*) ; 
 struct amdgpu_ras* kmalloc (int,int) ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_device*) ; 

int amdgpu_ras_init(struct amdgpu_device *adev)
{
	struct amdgpu_ras *con = amdgpu_ras_get_context(adev);

	if (con)
		return 0;

	con = kmalloc(sizeof(struct amdgpu_ras) +
			sizeof(struct ras_manager) * AMDGPU_RAS_BLOCK_COUNT,
			GFP_KERNEL|__GFP_ZERO);
	if (!con)
		return -ENOMEM;

	con->objs = (struct ras_manager *)(con + 1);

	amdgpu_ras_set_context(adev, con);

	amdgpu_ras_check_supported(adev, &con->hw_supported,
			&con->supported);
	if (!con->hw_supported) {
		amdgpu_ras_set_context(adev, NULL);
		kfree(con);
		return 0;
	}

	con->features = 0;
	INIT_LIST_HEAD(&con->head);
	/* Might need get this flag from vbios. */
	con->flags = RAS_DEFAULT_FLAGS;

	if (amdgpu_ras_recovery_init(adev))
		goto recovery_out;

	amdgpu_ras_mask &= AMDGPU_RAS_BLOCK_MASK;

	if (amdgpu_ras_fs_init(adev))
		goto fs_out;

	/* ras init for each ras block */
	if (adev->umc.funcs->ras_init)
		adev->umc.funcs->ras_init(adev);

	DRM_INFO("RAS INFO: ras initialized successfully, "
			"hardware ability[%x] ras_mask[%x]\n",
			con->hw_supported, con->supported);
	return 0;
fs_out:
	amdgpu_ras_recovery_fini(adev);
recovery_out:
	amdgpu_ras_set_context(adev, NULL);
	kfree(con);

	return -EINVAL;
}