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
struct drm_device {struct bochs_device* dev_private; } ;
struct bochs_device {struct drm_encoder encoder; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_ENCODER_DAC ; 
 int /*<<< orphan*/  bochs_encoder_encoder_funcs ; 
 int /*<<< orphan*/  bochs_encoder_helper_funcs ; 
 int /*<<< orphan*/  drm_encoder_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bochs_encoder_init(struct drm_device *dev)
{
	struct bochs_device *bochs = dev->dev_private;
	struct drm_encoder *encoder = &bochs->encoder;

	encoder->possible_crtcs = 0x1;
	drm_encoder_init(dev, encoder, &bochs_encoder_encoder_funcs,
			 DRM_MODE_ENCODER_DAC, NULL);
	drm_encoder_helper_add(encoder, &bochs_encoder_helper_funcs);
}