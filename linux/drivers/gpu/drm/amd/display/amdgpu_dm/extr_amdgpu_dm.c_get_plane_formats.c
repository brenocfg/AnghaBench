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
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_plane {int type; } ;
struct TYPE_2__ {int /*<<< orphan*/  nv12; } ;
struct dc_plane_cap {TYPE_1__ pixel_format_support; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DRM_FORMAT_NV12 ; 
#define  DRM_PLANE_TYPE_CURSOR 130 
#define  DRM_PLANE_TYPE_OVERLAY 129 
#define  DRM_PLANE_TYPE_PRIMARY 128 
 int /*<<< orphan*/ * cursor_formats ; 
 int /*<<< orphan*/ * overlay_formats ; 
 int /*<<< orphan*/ * rgb_formats ; 

__attribute__((used)) static int get_plane_formats(const struct drm_plane *plane,
			     const struct dc_plane_cap *plane_cap,
			     uint32_t *formats, int max_formats)
{
	int i, num_formats = 0;

	/*
	 * TODO: Query support for each group of formats directly from
	 * DC plane caps. This will require adding more formats to the
	 * caps list.
	 */

	switch (plane->type) {
	case DRM_PLANE_TYPE_PRIMARY:
		for (i = 0; i < ARRAY_SIZE(rgb_formats); ++i) {
			if (num_formats >= max_formats)
				break;

			formats[num_formats++] = rgb_formats[i];
		}

		if (plane_cap && plane_cap->pixel_format_support.nv12)
			formats[num_formats++] = DRM_FORMAT_NV12;
		break;

	case DRM_PLANE_TYPE_OVERLAY:
		for (i = 0; i < ARRAY_SIZE(overlay_formats); ++i) {
			if (num_formats >= max_formats)
				break;

			formats[num_formats++] = overlay_formats[i];
		}
		break;

	case DRM_PLANE_TYPE_CURSOR:
		for (i = 0; i < ARRAY_SIZE(cursor_formats); ++i) {
			if (num_formats >= max_formats)
				break;

			formats[num_formats++] = cursor_formats[i];
		}
		break;
	}

	return num_formats;
}