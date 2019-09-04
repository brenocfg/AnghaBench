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
struct cirrus_encoder {struct drm_encoder base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_ENCODER_DAC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cirrus_encoder_encoder_funcs ; 
 int /*<<< orphan*/  cirrus_encoder_helper_funcs ; 
 int /*<<< orphan*/  drm_encoder_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct cirrus_encoder* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_encoder *cirrus_encoder_init(struct drm_device *dev)
{
	struct drm_encoder *encoder;
	struct cirrus_encoder *cirrus_encoder;

	cirrus_encoder = kzalloc(sizeof(struct cirrus_encoder), GFP_KERNEL);
	if (!cirrus_encoder)
		return NULL;

	encoder = &cirrus_encoder->base;
	encoder->possible_crtcs = 0x1;

	drm_encoder_init(dev, encoder, &cirrus_encoder_encoder_funcs,
			 DRM_MODE_ENCODER_DAC, NULL);
	drm_encoder_helper_add(encoder, &cirrus_encoder_helper_funcs);

	return encoder;
}