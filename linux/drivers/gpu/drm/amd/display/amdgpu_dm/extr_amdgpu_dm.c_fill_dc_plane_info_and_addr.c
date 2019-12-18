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
typedef  int /*<<< orphan*/  uint64_t ;
struct drm_plane_state {int rotation; struct drm_framebuffer* fb; } ;
struct drm_framebuffer {TYPE_1__* format; } ;
struct drm_format_name_buf {int dummy; } ;
struct dc_plane_info {int visible; int /*<<< orphan*/  global_alpha_value; int /*<<< orphan*/  global_alpha; int /*<<< orphan*/  per_pixel_alpha; int /*<<< orphan*/  dcc; int /*<<< orphan*/  plane_size; int /*<<< orphan*/  tiling_info; void* rotation; int /*<<< orphan*/  format; int /*<<< orphan*/  color_space; scalar_t__ layer_index; int /*<<< orphan*/  stereo_format; } ;
struct dc_plane_address {int dummy; } ;
struct amdgpu_framebuffer {int dummy; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_2__ {int format; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
#define  DRM_FORMAT_ABGR2101010 143 
#define  DRM_FORMAT_ABGR8888 142 
#define  DRM_FORMAT_ARGB2101010 141 
#define  DRM_FORMAT_ARGB8888 140 
#define  DRM_FORMAT_C8 139 
#define  DRM_FORMAT_NV12 138 
#define  DRM_FORMAT_NV21 137 
#define  DRM_FORMAT_RGB565 136 
#define  DRM_FORMAT_XBGR2101010 135 
#define  DRM_FORMAT_XBGR8888 134 
#define  DRM_FORMAT_XRGB2101010 133 
#define  DRM_FORMAT_XRGB8888 132 
#define  DRM_MODE_ROTATE_0 131 
#define  DRM_MODE_ROTATE_180 130 
#define  DRM_MODE_ROTATE_270 129 
#define  DRM_MODE_ROTATE_90 128 
 int DRM_MODE_ROTATE_MASK ; 
 int EINVAL ; 
 int /*<<< orphan*/  PLANE_STEREO_FORMAT_NONE ; 
 void* ROTATION_ANGLE_0 ; 
 void* ROTATION_ANGLE_180 ; 
 void* ROTATION_ANGLE_270 ; 
 void* ROTATION_ANGLE_90 ; 
 int /*<<< orphan*/  SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010 ; 
 int /*<<< orphan*/  SURFACE_PIXEL_FORMAT_GRPH_ABGR8888 ; 
 int /*<<< orphan*/  SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010 ; 
 int /*<<< orphan*/  SURFACE_PIXEL_FORMAT_GRPH_ARGB8888 ; 
 int /*<<< orphan*/  SURFACE_PIXEL_FORMAT_GRPH_PALETA_256_COLORS ; 
 int /*<<< orphan*/  SURFACE_PIXEL_FORMAT_GRPH_RGB565 ; 
 int /*<<< orphan*/  SURFACE_PIXEL_FORMAT_VIDEO_420_YCbCr ; 
 int /*<<< orphan*/  SURFACE_PIXEL_FORMAT_VIDEO_420_YCrCb ; 
 int /*<<< orphan*/  drm_get_format_name (int,struct drm_format_name_buf*) ; 
 int /*<<< orphan*/  fill_blending_from_plane_state (struct drm_plane_state const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int fill_plane_buffer_attributes (struct amdgpu_device*,struct amdgpu_framebuffer const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/  const,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct dc_plane_address*) ; 
 int fill_plane_color_attributes (struct drm_plane_state const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct dc_plane_info*,int /*<<< orphan*/ ,int) ; 
 struct amdgpu_framebuffer* to_amdgpu_framebuffer (struct drm_framebuffer*) ; 

__attribute__((used)) static int
fill_dc_plane_info_and_addr(struct amdgpu_device *adev,
			    const struct drm_plane_state *plane_state,
			    const uint64_t tiling_flags,
			    struct dc_plane_info *plane_info,
			    struct dc_plane_address *address)
{
	const struct drm_framebuffer *fb = plane_state->fb;
	const struct amdgpu_framebuffer *afb =
		to_amdgpu_framebuffer(plane_state->fb);
	struct drm_format_name_buf format_name;
	int ret;

	memset(plane_info, 0, sizeof(*plane_info));

	switch (fb->format->format) {
	case DRM_FORMAT_C8:
		plane_info->format =
			SURFACE_PIXEL_FORMAT_GRPH_PALETA_256_COLORS;
		break;
	case DRM_FORMAT_RGB565:
		plane_info->format = SURFACE_PIXEL_FORMAT_GRPH_RGB565;
		break;
	case DRM_FORMAT_XRGB8888:
	case DRM_FORMAT_ARGB8888:
		plane_info->format = SURFACE_PIXEL_FORMAT_GRPH_ARGB8888;
		break;
	case DRM_FORMAT_XRGB2101010:
	case DRM_FORMAT_ARGB2101010:
		plane_info->format = SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010;
		break;
	case DRM_FORMAT_XBGR2101010:
	case DRM_FORMAT_ABGR2101010:
		plane_info->format = SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010;
		break;
	case DRM_FORMAT_XBGR8888:
	case DRM_FORMAT_ABGR8888:
		plane_info->format = SURFACE_PIXEL_FORMAT_GRPH_ABGR8888;
		break;
	case DRM_FORMAT_NV21:
		plane_info->format = SURFACE_PIXEL_FORMAT_VIDEO_420_YCbCr;
		break;
	case DRM_FORMAT_NV12:
		plane_info->format = SURFACE_PIXEL_FORMAT_VIDEO_420_YCrCb;
		break;
	default:
		DRM_ERROR(
			"Unsupported screen format %s\n",
			drm_get_format_name(fb->format->format, &format_name));
		return -EINVAL;
	}

	switch (plane_state->rotation & DRM_MODE_ROTATE_MASK) {
	case DRM_MODE_ROTATE_0:
		plane_info->rotation = ROTATION_ANGLE_0;
		break;
	case DRM_MODE_ROTATE_90:
		plane_info->rotation = ROTATION_ANGLE_90;
		break;
	case DRM_MODE_ROTATE_180:
		plane_info->rotation = ROTATION_ANGLE_180;
		break;
	case DRM_MODE_ROTATE_270:
		plane_info->rotation = ROTATION_ANGLE_270;
		break;
	default:
		plane_info->rotation = ROTATION_ANGLE_0;
		break;
	}

	plane_info->visible = true;
	plane_info->stereo_format = PLANE_STEREO_FORMAT_NONE;

	plane_info->layer_index = 0;

	ret = fill_plane_color_attributes(plane_state, plane_info->format,
					  &plane_info->color_space);
	if (ret)
		return ret;

	ret = fill_plane_buffer_attributes(adev, afb, plane_info->format,
					   plane_info->rotation, tiling_flags,
					   &plane_info->tiling_info,
					   &plane_info->plane_size,
					   &plane_info->dcc, address);
	if (ret)
		return ret;

	fill_blending_from_plane_state(
		plane_state, &plane_info->per_pixel_alpha,
		&plane_info->global_alpha, &plane_info->global_alpha_value);

	return 0;
}