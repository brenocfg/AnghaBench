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
struct TYPE_2__ {int mode_config_initialized; int /*<<< orphan*/  bios_hardcoded_edid; } ;
struct amdgpu_device {TYPE_1__ mode_info; int /*<<< orphan*/  ddev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dce_v8_0_afmt_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  dce_v8_0_audio_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_fini (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dce_v8_0_sw_fini(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	kfree(adev->mode_info.bios_hardcoded_edid);

	drm_kms_helper_poll_fini(adev->ddev);

	dce_v8_0_audio_fini(adev);

	dce_v8_0_afmt_fini(adev);

	drm_mode_config_cleanup(adev->ddev);
	adev->mode_info.mode_config_initialized = false;

	return 0;
}