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
struct drm_encoder {int /*<<< orphan*/  possible_crtcs; } ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct amdgpu_encoder {struct drm_encoder base; } ;
struct TYPE_2__ {struct drm_device* dev; } ;
struct amdgpu_dm_connector {TYPE_1__ base; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_ENCODER_DPMST ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  amdgpu_dm_encoder_funcs ; 
 int /*<<< orphan*/  amdgpu_dm_encoder_helper_funcs ; 
 int /*<<< orphan*/  amdgpu_dm_get_encoder_crtc_mask (struct amdgpu_device*) ; 
 int /*<<< orphan*/  drm_encoder_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct amdgpu_encoder* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct amdgpu_encoder *
dm_dp_create_fake_mst_encoder(struct amdgpu_dm_connector *connector)
{
	struct drm_device *dev = connector->base.dev;
	struct amdgpu_device *adev = dev->dev_private;
	struct amdgpu_encoder *amdgpu_encoder;
	struct drm_encoder *encoder;

	amdgpu_encoder = kzalloc(sizeof(*amdgpu_encoder), GFP_KERNEL);
	if (!amdgpu_encoder)
		return NULL;

	encoder = &amdgpu_encoder->base;
	encoder->possible_crtcs = amdgpu_dm_get_encoder_crtc_mask(adev);

	drm_encoder_init(
		dev,
		&amdgpu_encoder->base,
		&amdgpu_dm_encoder_funcs,
		DRM_MODE_ENCODER_DPMST,
		NULL);

	drm_encoder_helper_add(encoder, &amdgpu_dm_encoder_helper_funcs);

	return amdgpu_encoder;
}