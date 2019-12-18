#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_plane {TYPE_3__* funcs; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {scalar_t__ nv12; } ;
struct dc_plane_cap {TYPE_2__ pixel_format_support; scalar_t__ per_pixel_alpha; } ;
struct amdgpu_display_manager {TYPE_1__* adev; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* reset ) (struct drm_plane*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  ddev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 unsigned int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_COLOR_YCBCR_BT601 ; 
 int /*<<< orphan*/  DRM_COLOR_YCBCR_BT709 ; 
 int /*<<< orphan*/  DRM_COLOR_YCBCR_FULL_RANGE ; 
 int /*<<< orphan*/  DRM_COLOR_YCBCR_LIMITED_RANGE ; 
 int /*<<< orphan*/  DRM_MODE_BLEND_PIXEL_NONE ; 
 int /*<<< orphan*/  DRM_MODE_BLEND_PREMULTI ; 
 int /*<<< orphan*/  DRM_PLANE_TYPE_OVERLAY ; 
 int /*<<< orphan*/  DRM_PLANE_TYPE_PRIMARY ; 
 int EPERM ; 
 int /*<<< orphan*/  dm_plane_funcs ; 
 int /*<<< orphan*/  dm_plane_helper_funcs ; 
 int /*<<< orphan*/  drm_plane_create_alpha_property (struct drm_plane*) ; 
 int /*<<< orphan*/  drm_plane_create_blend_mode_property (struct drm_plane*,unsigned int) ; 
 int /*<<< orphan*/  drm_plane_create_color_properties (struct drm_plane*,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_plane_helper_add (struct drm_plane*,int /*<<< orphan*/ *) ; 
 int drm_universal_plane_init (int /*<<< orphan*/ ,struct drm_plane*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int get_plane_formats (struct drm_plane*,struct dc_plane_cap const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct drm_plane*) ; 

__attribute__((used)) static int amdgpu_dm_plane_init(struct amdgpu_display_manager *dm,
				struct drm_plane *plane,
				unsigned long possible_crtcs,
				const struct dc_plane_cap *plane_cap)
{
	uint32_t formats[32];
	int num_formats;
	int res = -EPERM;

	num_formats = get_plane_formats(plane, plane_cap, formats,
					ARRAY_SIZE(formats));

	res = drm_universal_plane_init(dm->adev->ddev, plane, possible_crtcs,
				       &dm_plane_funcs, formats, num_formats,
				       NULL, plane->type, NULL);
	if (res)
		return res;

	if (plane->type == DRM_PLANE_TYPE_OVERLAY &&
	    plane_cap && plane_cap->per_pixel_alpha) {
		unsigned int blend_caps = BIT(DRM_MODE_BLEND_PIXEL_NONE) |
					  BIT(DRM_MODE_BLEND_PREMULTI);

		drm_plane_create_alpha_property(plane);
		drm_plane_create_blend_mode_property(plane, blend_caps);
	}

	if (plane->type == DRM_PLANE_TYPE_PRIMARY &&
	    plane_cap && plane_cap->pixel_format_support.nv12) {
		/* This only affects YUV formats. */
		drm_plane_create_color_properties(
			plane,
			BIT(DRM_COLOR_YCBCR_BT601) |
			BIT(DRM_COLOR_YCBCR_BT709),
			BIT(DRM_COLOR_YCBCR_LIMITED_RANGE) |
			BIT(DRM_COLOR_YCBCR_FULL_RANGE),
			DRM_COLOR_YCBCR_BT709, DRM_COLOR_YCBCR_LIMITED_RANGE);
	}

	drm_plane_helper_add(plane, &dm_plane_helper_funcs);

	/* Create (reset) the plane state */
	if (plane->funcs->reset)
		plane->funcs->reset(plane);

	return 0;
}