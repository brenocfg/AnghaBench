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
struct mdp5_interface {scalar_t__ type; } ;
struct drm_encoder {int dummy; } ;
struct mdp5_encoder {int /*<<< orphan*/  intf_lock; struct mdp5_interface* intf; struct mdp5_ctl* ctl; struct drm_encoder base; } ;
struct mdp5_ctl {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int DRM_MODE_ENCODER_DSI ; 
 int DRM_MODE_ENCODER_TMDS ; 
 int ENOMEM ; 
 struct drm_encoder* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ INTF_DSI ; 
 int /*<<< orphan*/  bs_init (struct mdp5_encoder*) ; 
 int /*<<< orphan*/  drm_encoder_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 struct mdp5_encoder* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdp5_encoder_destroy (struct drm_encoder*) ; 
 int /*<<< orphan*/  mdp5_encoder_funcs ; 
 int /*<<< orphan*/  mdp5_encoder_helper_funcs ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct drm_encoder *mdp5_encoder_init(struct drm_device *dev,
				      struct mdp5_interface *intf,
				      struct mdp5_ctl *ctl)
{
	struct drm_encoder *encoder = NULL;
	struct mdp5_encoder *mdp5_encoder;
	int enc_type = (intf->type == INTF_DSI) ?
		DRM_MODE_ENCODER_DSI : DRM_MODE_ENCODER_TMDS;
	int ret;

	mdp5_encoder = kzalloc(sizeof(*mdp5_encoder), GFP_KERNEL);
	if (!mdp5_encoder) {
		ret = -ENOMEM;
		goto fail;
	}

	encoder = &mdp5_encoder->base;
	mdp5_encoder->ctl = ctl;
	mdp5_encoder->intf = intf;

	spin_lock_init(&mdp5_encoder->intf_lock);

	drm_encoder_init(dev, encoder, &mdp5_encoder_funcs, enc_type, NULL);

	drm_encoder_helper_add(encoder, &mdp5_encoder_helper_funcs);

	bs_init(mdp5_encoder);

	return encoder;

fail:
	if (encoder)
		mdp5_encoder_destroy(encoder);

	return ERR_PTR(ret);
}