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
struct drm_plane_state {int /*<<< orphan*/  crtc; struct drm_framebuffer* fb; } ;
struct drm_plane {int dummy; } ;
struct drm_framebuffer {TYPE_1__* format; } ;
struct TYPE_2__ {int format; } ;

/* Variables and functions */
#define  DRM_FORMAT_ARGB1555 136 
#define  DRM_FORMAT_ARGB4444 135 
#define  DRM_FORMAT_ARGB8888 134 
#define  DRM_FORMAT_RGB565 133 
#define  DRM_FORMAT_RGB888 132 
#define  DRM_FORMAT_XRGB1555 131 
#define  DRM_FORMAT_XRGB4444 130 
#define  DRM_FORMAT_XRGB8888 129 
#define  DRM_FORMAT_YUV422 128 
 int EINVAL ; 

__attribute__((used)) static int fsl_dcu_drm_plane_atomic_check(struct drm_plane *plane,
					  struct drm_plane_state *state)
{
	struct drm_framebuffer *fb = state->fb;

	if (!state->fb || !state->crtc)
		return 0;

	switch (fb->format->format) {
	case DRM_FORMAT_RGB565:
	case DRM_FORMAT_RGB888:
	case DRM_FORMAT_XRGB8888:
	case DRM_FORMAT_ARGB8888:
	case DRM_FORMAT_XRGB4444:
	case DRM_FORMAT_ARGB4444:
	case DRM_FORMAT_XRGB1555:
	case DRM_FORMAT_ARGB1555:
	case DRM_FORMAT_YUV422:
		return 0;
	default:
		return -EINVAL;
	}
}