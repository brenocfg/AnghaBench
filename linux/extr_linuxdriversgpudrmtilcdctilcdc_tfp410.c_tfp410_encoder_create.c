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
struct tfp410_module {int dummy; } ;
struct drm_encoder {int possible_crtcs; } ;
struct tfp410_encoder {struct drm_encoder base; struct tfp410_module* mod; int /*<<< orphan*/  dpms; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_DPMS_OFF ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_TMDS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct tfp410_encoder* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_encoder_cleanup (struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_encoder_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tfp410_encoder_funcs ; 
 int /*<<< orphan*/  tfp410_encoder_helper_funcs ; 

__attribute__((used)) static struct drm_encoder *tfp410_encoder_create(struct drm_device *dev,
		struct tfp410_module *mod)
{
	struct tfp410_encoder *tfp410_encoder;
	struct drm_encoder *encoder;
	int ret;

	tfp410_encoder = devm_kzalloc(dev->dev, sizeof(*tfp410_encoder),
				      GFP_KERNEL);
	if (!tfp410_encoder)
		return NULL;

	tfp410_encoder->dpms = DRM_MODE_DPMS_OFF;
	tfp410_encoder->mod = mod;

	encoder = &tfp410_encoder->base;
	encoder->possible_crtcs = 1;

	ret = drm_encoder_init(dev, encoder, &tfp410_encoder_funcs,
			DRM_MODE_ENCODER_TMDS, NULL);
	if (ret < 0)
		goto fail;

	drm_encoder_helper_add(encoder, &tfp410_encoder_helper_funcs);

	return encoder;

fail:
	drm_encoder_cleanup(encoder);
	return NULL;
}