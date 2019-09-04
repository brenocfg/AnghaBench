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
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_DPMS_ON ; 
 int /*<<< orphan*/  amdgpu_atombios_encoder_dpms (struct drm_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_atombios_scratch_regs_lock (struct amdgpu_device*,int) ; 

__attribute__((used)) static void dce_v11_0_encoder_commit(struct drm_encoder *encoder)
{
	struct drm_device *dev = encoder->dev;
	struct amdgpu_device *adev = dev->dev_private;

	/* need to call this here as we need the crtc set up */
	amdgpu_atombios_encoder_dpms(encoder, DRM_MODE_DPMS_ON);
	amdgpu_atombios_scratch_regs_lock(adev, false);
}