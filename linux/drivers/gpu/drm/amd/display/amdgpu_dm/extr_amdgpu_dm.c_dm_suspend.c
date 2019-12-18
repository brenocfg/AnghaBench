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
struct amdgpu_display_manager {int /*<<< orphan*/  dc; int /*<<< orphan*/  cached_state; } ;
struct amdgpu_device {int /*<<< orphan*/  ddev; struct amdgpu_display_manager dm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_ACPI_CM_POWER_STATE_D3 ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_dm_irq_suspend (struct amdgpu_device*) ; 
 int /*<<< orphan*/  dc_set_power_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_atomic_helper_suspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3_handle_mst (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dm_suspend(void *handle)
{
	struct amdgpu_device *adev = handle;
	struct amdgpu_display_manager *dm = &adev->dm;
	int ret = 0;

	WARN_ON(adev->dm.cached_state);
	adev->dm.cached_state = drm_atomic_helper_suspend(adev->ddev);

	s3_handle_mst(adev->ddev, true);

	amdgpu_dm_irq_suspend(adev);


	dc_set_power_state(dm->dc, DC_ACPI_CM_POWER_STATE_D3);

	return ret;
}