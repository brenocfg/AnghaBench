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
struct mdp4_dtv_encoder {void* mdp_clk; void* hdmi_clk; struct drm_encoder base; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_TMDS ; 
 int ENOMEM ; 
 struct drm_encoder* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  bs_init (struct mdp4_dtv_encoder*) ; 
 void* devm_clk_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  drm_encoder_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mdp4_dtv_encoder* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdp4_dtv_encoder_destroy (struct drm_encoder*) ; 
 int /*<<< orphan*/  mdp4_dtv_encoder_funcs ; 
 int /*<<< orphan*/  mdp4_dtv_encoder_helper_funcs ; 

struct drm_encoder *mdp4_dtv_encoder_init(struct drm_device *dev)
{
	struct drm_encoder *encoder = NULL;
	struct mdp4_dtv_encoder *mdp4_dtv_encoder;
	int ret;

	mdp4_dtv_encoder = kzalloc(sizeof(*mdp4_dtv_encoder), GFP_KERNEL);
	if (!mdp4_dtv_encoder) {
		ret = -ENOMEM;
		goto fail;
	}

	encoder = &mdp4_dtv_encoder->base;

	drm_encoder_init(dev, encoder, &mdp4_dtv_encoder_funcs,
			 DRM_MODE_ENCODER_TMDS, NULL);
	drm_encoder_helper_add(encoder, &mdp4_dtv_encoder_helper_funcs);

	mdp4_dtv_encoder->hdmi_clk = devm_clk_get(dev->dev, "hdmi_clk");
	if (IS_ERR(mdp4_dtv_encoder->hdmi_clk)) {
		DRM_DEV_ERROR(dev->dev, "failed to get hdmi_clk\n");
		ret = PTR_ERR(mdp4_dtv_encoder->hdmi_clk);
		goto fail;
	}

	mdp4_dtv_encoder->mdp_clk = devm_clk_get(dev->dev, "tv_clk");
	if (IS_ERR(mdp4_dtv_encoder->mdp_clk)) {
		DRM_DEV_ERROR(dev->dev, "failed to get tv_clk\n");
		ret = PTR_ERR(mdp4_dtv_encoder->mdp_clk);
		goto fail;
	}

	bs_init(mdp4_dtv_encoder);

	return encoder;

fail:
	if (encoder)
		mdp4_dtv_encoder_destroy(encoder);

	return ERR_PTR(ret);
}