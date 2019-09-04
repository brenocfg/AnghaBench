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
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct amdgpu_encoder_atom_dig {TYPE_1__* afmt; } ;
struct amdgpu_encoder {int /*<<< orphan*/  encoder_id; struct amdgpu_encoder_atom_dig* enc_priv; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_2__ {int enabled; int /*<<< orphan*/  offset; int /*<<< orphan*/ * pin; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dce_v6_0_audio_enable (struct amdgpu_device*,int /*<<< orphan*/ *,int) ; 
 struct amdgpu_encoder* to_amdgpu_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void dce_v6_0_afmt_enable(struct drm_encoder *encoder, bool enable)
{
	struct drm_device *dev = encoder->dev;
	struct amdgpu_device *adev = dev->dev_private;
	struct amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	struct amdgpu_encoder_atom_dig *dig = amdgpu_encoder->enc_priv;

	if (!dig || !dig->afmt)
		return;

	/* Silent, r600_hdmi_enable will raise WARN for us */
	if (enable && dig->afmt->enabled)
		return;

	if (!enable && !dig->afmt->enabled)
		return;

	if (!enable && dig->afmt->pin) {
		dce_v6_0_audio_enable(adev, dig->afmt->pin, false);
		dig->afmt->pin = NULL;
	}

	dig->afmt->enabled = enable;

	DRM_DEBUG("%sabling AFMT interface @ 0x%04X for encoder 0x%x\n",
		  enable ? "En" : "Dis", dig->afmt->offset, amdgpu_encoder->encoder_id);
}