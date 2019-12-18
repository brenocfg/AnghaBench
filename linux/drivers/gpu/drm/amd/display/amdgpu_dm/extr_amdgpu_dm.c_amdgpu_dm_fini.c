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
struct TYPE_2__ {int /*<<< orphan*/  dc_lock; int /*<<< orphan*/  audio_lock; int /*<<< orphan*/ * freesync_module; int /*<<< orphan*/ * cgs_device; scalar_t__ dc; } ;
struct amdgpu_device {TYPE_1__ dm; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_cgs_destroy_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_dm_audio_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_dm_destroy_drm_device (TYPE_1__*) ; 
 int /*<<< orphan*/  dc_destroy (scalar_t__*) ; 
 int /*<<< orphan*/  mod_freesync_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void amdgpu_dm_fini(struct amdgpu_device *adev)
{
	amdgpu_dm_audio_fini(adev);

	amdgpu_dm_destroy_drm_device(&adev->dm);

	/* DC Destroy TODO: Replace destroy DAL */
	if (adev->dm.dc)
		dc_destroy(&adev->dm.dc);
	/*
	 * TODO: pageflip, vlank interrupt
	 *
	 * amdgpu_dm_irq_fini(adev);
	 */

	if (adev->dm.cgs_device) {
		amdgpu_cgs_destroy_device(adev->dm.cgs_device);
		adev->dm.cgs_device = NULL;
	}
	if (adev->dm.freesync_module) {
		mod_freesync_destroy(adev->dm.freesync_module);
		adev->dm.freesync_module = NULL;
	}

	mutex_destroy(&adev->dm.audio_lock);
	mutex_destroy(&adev->dm.dc_lock);

	return;
}