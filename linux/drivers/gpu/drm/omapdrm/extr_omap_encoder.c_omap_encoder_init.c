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
struct drm_encoder {int dummy; } ;
struct omap_encoder {struct drm_encoder base; struct omap_dss_device* output; } ;
struct omap_dss_device {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_ENCODER_TMDS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_encoder_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct omap_encoder* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_encoder_destroy (struct drm_encoder*) ; 
 int /*<<< orphan*/  omap_encoder_funcs ; 
 int /*<<< orphan*/  omap_encoder_helper_funcs ; 

struct drm_encoder *omap_encoder_init(struct drm_device *dev,
				      struct omap_dss_device *output)
{
	struct drm_encoder *encoder = NULL;
	struct omap_encoder *omap_encoder;

	omap_encoder = kzalloc(sizeof(*omap_encoder), GFP_KERNEL);
	if (!omap_encoder)
		goto fail;

	omap_encoder->output = output;

	encoder = &omap_encoder->base;

	drm_encoder_init(dev, encoder, &omap_encoder_funcs,
			 DRM_MODE_ENCODER_TMDS, NULL);
	drm_encoder_helper_add(encoder, &omap_encoder_helper_funcs);

	return encoder;

fail:
	if (encoder)
		omap_encoder_destroy(encoder);

	return NULL;
}