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
struct drm_encoder {int possible_crtcs; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_ENCODER_TMDS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_encoder_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct drm_encoder* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udl_enc_funcs ; 
 int /*<<< orphan*/  udl_helper_funcs ; 

struct drm_encoder *udl_encoder_init(struct drm_device *dev)
{
	struct drm_encoder *encoder;

	encoder = kzalloc(sizeof(struct drm_encoder), GFP_KERNEL);
	if (!encoder)
		return NULL;

	drm_encoder_init(dev, encoder, &udl_enc_funcs, DRM_MODE_ENCODER_TMDS,
			 NULL);
	drm_encoder_helper_add(encoder, &udl_helper_funcs);
	encoder->possible_crtcs = 1;
	return encoder;
}