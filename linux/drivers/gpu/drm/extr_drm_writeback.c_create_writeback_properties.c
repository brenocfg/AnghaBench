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
struct TYPE_2__ {struct drm_property* writeback_out_fence_ptr_property; struct drm_property* writeback_pixel_formats_property; struct drm_property* writeback_fb_id_property; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_OBJECT_FB ; 
 int DRM_MODE_PROP_ATOMIC ; 
 int DRM_MODE_PROP_BLOB ; 
 int DRM_MODE_PROP_IMMUTABLE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  U64_MAX ; 
 struct drm_property* drm_property_create (struct drm_device*,int,char*,int /*<<< orphan*/ ) ; 
 struct drm_property* drm_property_create_object (struct drm_device*,int,char*,int /*<<< orphan*/ ) ; 
 struct drm_property* drm_property_create_range (struct drm_device*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int create_writeback_properties(struct drm_device *dev)
{
	struct drm_property *prop;

	if (!dev->mode_config.writeback_fb_id_property) {
		prop = drm_property_create_object(dev, DRM_MODE_PROP_ATOMIC,
						  "WRITEBACK_FB_ID",
						  DRM_MODE_OBJECT_FB);
		if (!prop)
			return -ENOMEM;
		dev->mode_config.writeback_fb_id_property = prop;
	}

	if (!dev->mode_config.writeback_pixel_formats_property) {
		prop = drm_property_create(dev, DRM_MODE_PROP_BLOB |
					   DRM_MODE_PROP_ATOMIC |
					   DRM_MODE_PROP_IMMUTABLE,
					   "WRITEBACK_PIXEL_FORMATS", 0);
		if (!prop)
			return -ENOMEM;
		dev->mode_config.writeback_pixel_formats_property = prop;
	}

	if (!dev->mode_config.writeback_out_fence_ptr_property) {
		prop = drm_property_create_range(dev, DRM_MODE_PROP_ATOMIC,
						 "WRITEBACK_OUT_FENCE_PTR", 0,
						 U64_MAX);
		if (!prop)
			return -ENOMEM;
		dev->mode_config.writeback_out_fence_ptr_property = prop;
	}

	return 0;
}