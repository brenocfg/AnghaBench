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
struct mdp4_dsi_encoder {struct drm_encoder base; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_ENCODER_DSI ; 
 int ENOMEM ; 
 struct drm_encoder* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_encoder_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mdp4_dsi_encoder* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdp4_dsi_encoder_destroy (struct drm_encoder*) ; 
 int /*<<< orphan*/  mdp4_dsi_encoder_funcs ; 
 int /*<<< orphan*/  mdp4_dsi_encoder_helper_funcs ; 

struct drm_encoder *mdp4_dsi_encoder_init(struct drm_device *dev)
{
	struct drm_encoder *encoder = NULL;
	struct mdp4_dsi_encoder *mdp4_dsi_encoder;
	int ret;

	mdp4_dsi_encoder = kzalloc(sizeof(*mdp4_dsi_encoder), GFP_KERNEL);
	if (!mdp4_dsi_encoder) {
		ret = -ENOMEM;
		goto fail;
	}

	encoder = &mdp4_dsi_encoder->base;

	drm_encoder_init(dev, encoder, &mdp4_dsi_encoder_funcs,
			 DRM_MODE_ENCODER_DSI, NULL);
	drm_encoder_helper_add(encoder, &mdp4_dsi_encoder_helper_funcs);

	return encoder;

fail:
	if (encoder)
		mdp4_dsi_encoder_destroy(encoder);

	return ERR_PTR(ret);
}