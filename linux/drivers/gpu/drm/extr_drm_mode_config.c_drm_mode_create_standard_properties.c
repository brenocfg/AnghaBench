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
struct drm_property {int dummy; } ;
struct TYPE_2__ {struct drm_property* modifiers_property; struct drm_property* gamma_lut_size_property; struct drm_property* gamma_lut_property; struct drm_property* ctm_property; struct drm_property* degamma_lut_size_property; struct drm_property* degamma_lut_property; struct drm_property* prop_vrr_enabled; struct drm_property* prop_mode_id; struct drm_property* prop_active; struct drm_property* prop_fb_damage_clips; struct drm_property* prop_crtc_id; struct drm_property* prop_out_fence_ptr; struct drm_property* prop_in_fence_fd; struct drm_property* prop_fb_id; struct drm_property* prop_crtc_h; struct drm_property* prop_crtc_w; struct drm_property* prop_crtc_y; struct drm_property* prop_crtc_x; struct drm_property* prop_src_h; struct drm_property* prop_src_w; struct drm_property* prop_src_y; struct drm_property* prop_src_x; struct drm_property* plane_type_property; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_MODE_OBJECT_CRTC ; 
 int /*<<< orphan*/  DRM_MODE_OBJECT_FB ; 
 int DRM_MODE_PROP_ATOMIC ; 
 int DRM_MODE_PROP_BLOB ; 
 int DRM_MODE_PROP_IMMUTABLE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INT_MAX ; 
 int INT_MIN ; 
 int /*<<< orphan*/  U64_MAX ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int drm_connector_create_standard_properties (struct drm_device*) ; 
 int /*<<< orphan*/  drm_plane_type_enum_list ; 
 struct drm_property* drm_property_create (struct drm_device*,int,char*,int /*<<< orphan*/ ) ; 
 struct drm_property* drm_property_create_bool (struct drm_device*,int,char*) ; 
 struct drm_property* drm_property_create_enum (struct drm_device*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_property* drm_property_create_object (struct drm_device*,int,char*,int /*<<< orphan*/ ) ; 
 struct drm_property* drm_property_create_range (struct drm_device*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_property* drm_property_create_signed_range (struct drm_device*,int,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drm_mode_create_standard_properties(struct drm_device *dev)
{
	struct drm_property *prop;
	int ret;

	ret = drm_connector_create_standard_properties(dev);
	if (ret)
		return ret;

	prop = drm_property_create_enum(dev, DRM_MODE_PROP_IMMUTABLE,
					"type", drm_plane_type_enum_list,
					ARRAY_SIZE(drm_plane_type_enum_list));
	if (!prop)
		return -ENOMEM;
	dev->mode_config.plane_type_property = prop;

	prop = drm_property_create_range(dev, DRM_MODE_PROP_ATOMIC,
			"SRC_X", 0, UINT_MAX);
	if (!prop)
		return -ENOMEM;
	dev->mode_config.prop_src_x = prop;

	prop = drm_property_create_range(dev, DRM_MODE_PROP_ATOMIC,
			"SRC_Y", 0, UINT_MAX);
	if (!prop)
		return -ENOMEM;
	dev->mode_config.prop_src_y = prop;

	prop = drm_property_create_range(dev, DRM_MODE_PROP_ATOMIC,
			"SRC_W", 0, UINT_MAX);
	if (!prop)
		return -ENOMEM;
	dev->mode_config.prop_src_w = prop;

	prop = drm_property_create_range(dev, DRM_MODE_PROP_ATOMIC,
			"SRC_H", 0, UINT_MAX);
	if (!prop)
		return -ENOMEM;
	dev->mode_config.prop_src_h = prop;

	prop = drm_property_create_signed_range(dev, DRM_MODE_PROP_ATOMIC,
			"CRTC_X", INT_MIN, INT_MAX);
	if (!prop)
		return -ENOMEM;
	dev->mode_config.prop_crtc_x = prop;

	prop = drm_property_create_signed_range(dev, DRM_MODE_PROP_ATOMIC,
			"CRTC_Y", INT_MIN, INT_MAX);
	if (!prop)
		return -ENOMEM;
	dev->mode_config.prop_crtc_y = prop;

	prop = drm_property_create_range(dev, DRM_MODE_PROP_ATOMIC,
			"CRTC_W", 0, INT_MAX);
	if (!prop)
		return -ENOMEM;
	dev->mode_config.prop_crtc_w = prop;

	prop = drm_property_create_range(dev, DRM_MODE_PROP_ATOMIC,
			"CRTC_H", 0, INT_MAX);
	if (!prop)
		return -ENOMEM;
	dev->mode_config.prop_crtc_h = prop;

	prop = drm_property_create_object(dev, DRM_MODE_PROP_ATOMIC,
			"FB_ID", DRM_MODE_OBJECT_FB);
	if (!prop)
		return -ENOMEM;
	dev->mode_config.prop_fb_id = prop;

	prop = drm_property_create_signed_range(dev, DRM_MODE_PROP_ATOMIC,
			"IN_FENCE_FD", -1, INT_MAX);
	if (!prop)
		return -ENOMEM;
	dev->mode_config.prop_in_fence_fd = prop;

	prop = drm_property_create_range(dev, DRM_MODE_PROP_ATOMIC,
			"OUT_FENCE_PTR", 0, U64_MAX);
	if (!prop)
		return -ENOMEM;
	dev->mode_config.prop_out_fence_ptr = prop;

	prop = drm_property_create_object(dev, DRM_MODE_PROP_ATOMIC,
			"CRTC_ID", DRM_MODE_OBJECT_CRTC);
	if (!prop)
		return -ENOMEM;
	dev->mode_config.prop_crtc_id = prop;

	prop = drm_property_create(dev,
			DRM_MODE_PROP_ATOMIC | DRM_MODE_PROP_BLOB,
			"FB_DAMAGE_CLIPS", 0);
	if (!prop)
		return -ENOMEM;
	dev->mode_config.prop_fb_damage_clips = prop;

	prop = drm_property_create_bool(dev, DRM_MODE_PROP_ATOMIC,
			"ACTIVE");
	if (!prop)
		return -ENOMEM;
	dev->mode_config.prop_active = prop;

	prop = drm_property_create(dev,
			DRM_MODE_PROP_ATOMIC | DRM_MODE_PROP_BLOB,
			"MODE_ID", 0);
	if (!prop)
		return -ENOMEM;
	dev->mode_config.prop_mode_id = prop;

	prop = drm_property_create_bool(dev, 0,
			"VRR_ENABLED");
	if (!prop)
		return -ENOMEM;
	dev->mode_config.prop_vrr_enabled = prop;

	prop = drm_property_create(dev,
			DRM_MODE_PROP_BLOB,
			"DEGAMMA_LUT", 0);
	if (!prop)
		return -ENOMEM;
	dev->mode_config.degamma_lut_property = prop;

	prop = drm_property_create_range(dev,
			DRM_MODE_PROP_IMMUTABLE,
			"DEGAMMA_LUT_SIZE", 0, UINT_MAX);
	if (!prop)
		return -ENOMEM;
	dev->mode_config.degamma_lut_size_property = prop;

	prop = drm_property_create(dev,
			DRM_MODE_PROP_BLOB,
			"CTM", 0);
	if (!prop)
		return -ENOMEM;
	dev->mode_config.ctm_property = prop;

	prop = drm_property_create(dev,
			DRM_MODE_PROP_BLOB,
			"GAMMA_LUT", 0);
	if (!prop)
		return -ENOMEM;
	dev->mode_config.gamma_lut_property = prop;

	prop = drm_property_create_range(dev,
			DRM_MODE_PROP_IMMUTABLE,
			"GAMMA_LUT_SIZE", 0, UINT_MAX);
	if (!prop)
		return -ENOMEM;
	dev->mode_config.gamma_lut_size_property = prop;

	prop = drm_property_create(dev,
				   DRM_MODE_PROP_IMMUTABLE | DRM_MODE_PROP_BLOB,
				   "IN_FORMATS", 0);
	if (!prop)
		return -ENOMEM;
	dev->mode_config.modifiers_property = prop;

	return 0;
}