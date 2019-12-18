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
struct drm_mode_object {int dummy; } ;
struct drm_plane {struct drm_mode_object base; } ;
struct drm_device {struct armada_private* dev_private; } ;
struct armada_private {int /*<<< orphan*/  saturation_prop; int /*<<< orphan*/  contrast_prop; int /*<<< orphan*/  brightness_prop; int /*<<< orphan*/  colorkey_mode_prop; int /*<<< orphan*/  colorkey_alpha_prop; int /*<<< orphan*/  colorkey_val_prop; int /*<<< orphan*/  colorkey_max_prop; int /*<<< orphan*/  colorkey_min_prop; int /*<<< orphan*/  colorkey_prop; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int CKMODE_RGB ; 
 int DEFAULT_BRIGHTNESS ; 
 int DEFAULT_CONTRAST ; 
 int /*<<< orphan*/  DEFAULT_ENCODING ; 
 int DEFAULT_SATURATION ; 
 int /*<<< orphan*/  DRM_COLOR_YCBCR_BT601 ; 
 int /*<<< orphan*/  DRM_COLOR_YCBCR_BT709 ; 
 int /*<<< orphan*/  DRM_COLOR_YCBCR_LIMITED_RANGE ; 
 int /*<<< orphan*/  DRM_PLANE_TYPE_OVERLAY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int armada_overlay_create_properties (struct drm_device*) ; 
 int /*<<< orphan*/  armada_overlay_plane_helper_funcs ; 
 int /*<<< orphan*/  armada_ovl_formats ; 
 int /*<<< orphan*/  armada_ovl_plane_funcs ; 
 int /*<<< orphan*/  drm_object_attach_property (struct drm_mode_object*,int /*<<< orphan*/ ,int) ; 
 int drm_plane_create_color_properties (struct drm_plane*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_plane_helper_add (struct drm_plane*,int /*<<< orphan*/ *) ; 
 int drm_universal_plane_init (struct drm_device*,struct drm_plane*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct drm_plane*) ; 
 struct drm_plane* kzalloc (int,int /*<<< orphan*/ ) ; 

int armada_overlay_plane_create(struct drm_device *dev, unsigned long crtcs)
{
	struct armada_private *priv = dev->dev_private;
	struct drm_mode_object *mobj;
	struct drm_plane *overlay;
	int ret;

	ret = armada_overlay_create_properties(dev);
	if (ret)
		return ret;

	overlay = kzalloc(sizeof(*overlay), GFP_KERNEL);
	if (!overlay)
		return -ENOMEM;

	drm_plane_helper_add(overlay, &armada_overlay_plane_helper_funcs);

	ret = drm_universal_plane_init(dev, overlay, crtcs,
				       &armada_ovl_plane_funcs,
				       armada_ovl_formats,
				       ARRAY_SIZE(armada_ovl_formats),
				       NULL,
				       DRM_PLANE_TYPE_OVERLAY, NULL);
	if (ret) {
		kfree(overlay);
		return ret;
	}

	mobj = &overlay->base;
	drm_object_attach_property(mobj, priv->colorkey_prop,
				   0x0101fe);
	drm_object_attach_property(mobj, priv->colorkey_min_prop,
				   0x0101fe);
	drm_object_attach_property(mobj, priv->colorkey_max_prop,
				   0x0101fe);
	drm_object_attach_property(mobj, priv->colorkey_val_prop,
				   0x0101fe);
	drm_object_attach_property(mobj, priv->colorkey_alpha_prop,
				   0x000000);
	drm_object_attach_property(mobj, priv->colorkey_mode_prop,
				   CKMODE_RGB);
	drm_object_attach_property(mobj, priv->brightness_prop,
				   256 + DEFAULT_BRIGHTNESS);
	drm_object_attach_property(mobj, priv->contrast_prop,
				   DEFAULT_CONTRAST);
	drm_object_attach_property(mobj, priv->saturation_prop,
				   DEFAULT_SATURATION);

	ret = drm_plane_create_color_properties(overlay,
						BIT(DRM_COLOR_YCBCR_BT601) |
						BIT(DRM_COLOR_YCBCR_BT709),
						BIT(DRM_COLOR_YCBCR_LIMITED_RANGE),
						DEFAULT_ENCODING,
						DRM_COLOR_YCBCR_LIMITED_RANGE);

	return ret;
}