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
struct mga_encoder {struct drm_encoder base; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_ENCODER_DAC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_encoder_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mga_encoder* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mga_encoder_encoder_funcs ; 
 int /*<<< orphan*/  mga_encoder_helper_funcs ; 

__attribute__((used)) static struct drm_encoder *mga_encoder_init(struct drm_device *dev)
{
	struct drm_encoder *encoder;
	struct mga_encoder *mga_encoder;

	mga_encoder = kzalloc(sizeof(struct mga_encoder), GFP_KERNEL);
	if (!mga_encoder)
		return NULL;

	encoder = &mga_encoder->base;
	encoder->possible_crtcs = 0x1;

	drm_encoder_init(dev, encoder, &mga_encoder_encoder_funcs,
			 DRM_MODE_ENCODER_DAC, NULL);
	drm_encoder_helper_add(encoder, &mga_encoder_helper_funcs);

	return encoder;
}