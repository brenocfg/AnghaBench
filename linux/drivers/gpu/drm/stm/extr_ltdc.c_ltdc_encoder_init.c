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
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct drm_encoder {TYPE_1__ base; scalar_t__ possible_clones; int /*<<< orphan*/  possible_crtcs; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct drm_bridge {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC_MASK ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_DPI ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct drm_encoder* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int drm_bridge_attach (struct drm_encoder*,struct drm_bridge*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_cleanup (struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ltdc_encoder_funcs ; 

__attribute__((used)) static int ltdc_encoder_init(struct drm_device *ddev, struct drm_bridge *bridge)
{
	struct drm_encoder *encoder;
	int ret;

	encoder = devm_kzalloc(ddev->dev, sizeof(*encoder), GFP_KERNEL);
	if (!encoder)
		return -ENOMEM;

	encoder->possible_crtcs = CRTC_MASK;
	encoder->possible_clones = 0;	/* No cloning support */

	drm_encoder_init(ddev, encoder, &ltdc_encoder_funcs,
			 DRM_MODE_ENCODER_DPI, NULL);

	ret = drm_bridge_attach(encoder, bridge, NULL);
	if (ret) {
		drm_encoder_cleanup(encoder);
		return -EINVAL;
	}

	DRM_DEBUG_DRIVER("Bridge encoder:%d created\n", encoder->base.id);

	return 0;
}