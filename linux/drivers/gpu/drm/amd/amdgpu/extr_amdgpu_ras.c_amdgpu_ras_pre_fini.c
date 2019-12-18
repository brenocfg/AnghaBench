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
struct amdgpu_ras {int dummy; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_ras_disable_all_features (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 struct amdgpu_ras* amdgpu_ras_get_context (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_ras_recovery_fini (struct amdgpu_device*) ; 

int amdgpu_ras_pre_fini(struct amdgpu_device *adev)
{
	struct amdgpu_ras *con = amdgpu_ras_get_context(adev);

	if (!con)
		return 0;

	/* Need disable ras on all IPs here before ip [hw/sw]fini */
	amdgpu_ras_disable_all_features(adev, 0);
	amdgpu_ras_recovery_fini(adev);
	return 0;
}