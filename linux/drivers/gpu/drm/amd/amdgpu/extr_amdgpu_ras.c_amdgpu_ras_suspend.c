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
struct amdgpu_ras {scalar_t__ features; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_ras_disable_all_features (struct amdgpu_device*,int) ; 
 struct amdgpu_ras* amdgpu_ras_get_context (struct amdgpu_device*) ; 

void amdgpu_ras_suspend(struct amdgpu_device *adev)
{
	struct amdgpu_ras *con = amdgpu_ras_get_context(adev);

	if (!con)
		return;

	amdgpu_ras_disable_all_features(adev, 0);
	/* Make sure all ras objects are disabled. */
	if (con->features)
		amdgpu_ras_disable_all_features(adev, 1);
}