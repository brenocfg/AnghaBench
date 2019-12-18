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
struct radeon_encoder_mst {int /*<<< orphan*/  primary; struct radeon_connector* connector; } ;
struct drm_encoder {int possible_crtcs; } ;
struct radeon_encoder {int is_mst_encoder; struct radeon_encoder_mst* enc_priv; struct drm_encoder base; } ;
struct radeon_device {int num_crtc; } ;
struct TYPE_2__ {struct drm_connector_helper_funcs* helper_private; struct drm_device* dev; } ;
struct radeon_connector {TYPE_1__ base; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_connector_helper_funcs {struct drm_encoder* (* best_encoder ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,struct drm_encoder*) ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_DPMST ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_encoder_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct radeon_encoder*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_dp_mst_enc_funcs ; 
 int /*<<< orphan*/  radeon_mst_helper_funcs ; 
 struct drm_encoder* stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  to_radeon_encoder (struct drm_encoder*) ; 

__attribute__((used)) static struct radeon_encoder *
radeon_dp_create_fake_mst_encoder(struct radeon_connector *connector)
{
	struct drm_device *dev = connector->base.dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_encoder *radeon_encoder;
	struct radeon_encoder_mst *mst_enc;
	struct drm_encoder *encoder;
	const struct drm_connector_helper_funcs *connector_funcs = connector->base.helper_private;
	struct drm_encoder *enc_master = connector_funcs->best_encoder(&connector->base);

	DRM_DEBUG_KMS("enc master is %p\n", enc_master);
	radeon_encoder = kzalloc(sizeof(*radeon_encoder), GFP_KERNEL);
	if (!radeon_encoder)
		return NULL;

	radeon_encoder->enc_priv = kzalloc(sizeof(*mst_enc), GFP_KERNEL);
	if (!radeon_encoder->enc_priv) {
		kfree(radeon_encoder);
		return NULL;
	}
	encoder = &radeon_encoder->base;
	switch (rdev->num_crtc) {
	case 1:
		encoder->possible_crtcs = 0x1;
		break;
	case 2:
	default:
		encoder->possible_crtcs = 0x3;
		break;
	case 4:
		encoder->possible_crtcs = 0xf;
		break;
	case 6:
		encoder->possible_crtcs = 0x3f;
		break;
	}

	drm_encoder_init(dev, &radeon_encoder->base, &radeon_dp_mst_enc_funcs,
			 DRM_MODE_ENCODER_DPMST, NULL);
	drm_encoder_helper_add(encoder, &radeon_mst_helper_funcs);

	mst_enc = radeon_encoder->enc_priv;
	mst_enc->connector = connector;
	mst_enc->primary = to_radeon_encoder(enc_master);
	radeon_encoder->is_mst_encoder = true;
	return radeon_encoder;
}