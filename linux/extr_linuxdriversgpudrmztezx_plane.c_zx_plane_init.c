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
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_plane {int dummy; } ;
struct zx_plane {struct device* dev; struct drm_plane plane; } ;
struct drm_plane_helper_funcs {int dummy; } ;
struct drm_device {int dummy; } ;
struct device {int dummy; } ;
typedef  enum drm_plane_type { ____Placeholder_drm_plane_type } drm_plane_type ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*,int) ; 
#define  DRM_PLANE_TYPE_OVERLAY 129 
#define  DRM_PLANE_TYPE_PRIMARY 128 
 int ENODEV ; 
 int /*<<< orphan*/  VOU_CRTC_MASK ; 
 int /*<<< orphan*/  drm_plane_helper_add (struct drm_plane*,struct drm_plane_helper_funcs const*) ; 
 int drm_universal_plane_init (struct drm_device*,struct drm_plane*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gl_formats ; 
 int /*<<< orphan*/ * vl_formats ; 
 struct drm_plane_helper_funcs zx_gl_plane_helper_funcs ; 
 int /*<<< orphan*/  zx_plane_funcs ; 
 int /*<<< orphan*/  zx_plane_hbsc_init (struct zx_plane*) ; 
 struct drm_plane_helper_funcs zx_vl_plane_helper_funcs ; 

int zx_plane_init(struct drm_device *drm, struct zx_plane *zplane,
		  enum drm_plane_type type)
{
	const struct drm_plane_helper_funcs *helper;
	struct drm_plane *plane = &zplane->plane;
	struct device *dev = zplane->dev;
	const uint32_t *formats;
	unsigned int format_count;
	int ret;

	zx_plane_hbsc_init(zplane);

	switch (type) {
	case DRM_PLANE_TYPE_PRIMARY:
		helper = &zx_gl_plane_helper_funcs;
		formats = gl_formats;
		format_count = ARRAY_SIZE(gl_formats);
		break;
	case DRM_PLANE_TYPE_OVERLAY:
		helper = &zx_vl_plane_helper_funcs;
		formats = vl_formats;
		format_count = ARRAY_SIZE(vl_formats);
		break;
	default:
		return -ENODEV;
	}

	ret = drm_universal_plane_init(drm, plane, VOU_CRTC_MASK,
				       &zx_plane_funcs, formats, format_count,
				       NULL, type, NULL);
	if (ret) {
		DRM_DEV_ERROR(dev, "failed to init universal plane: %d\n", ret);
		return ret;
	}

	drm_plane_helper_add(plane, helper);

	return 0;
}