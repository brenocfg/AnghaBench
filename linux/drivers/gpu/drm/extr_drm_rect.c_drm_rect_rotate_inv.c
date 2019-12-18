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
struct drm_rect {scalar_t__ y1; scalar_t__ y2; scalar_t__ x1; scalar_t__ x2; } ;

/* Variables and functions */
 unsigned int DRM_MODE_REFLECT_X ; 
 unsigned int DRM_MODE_REFLECT_Y ; 
#define  DRM_MODE_ROTATE_0 131 
#define  DRM_MODE_ROTATE_180 130 
#define  DRM_MODE_ROTATE_270 129 
#define  DRM_MODE_ROTATE_90 128 
 unsigned int DRM_MODE_ROTATE_MASK ; 

void drm_rect_rotate_inv(struct drm_rect *r,
			 int width, int height,
			 unsigned int rotation)
{
	struct drm_rect tmp;

	switch (rotation & DRM_MODE_ROTATE_MASK) {
	case DRM_MODE_ROTATE_0:
		break;
	case DRM_MODE_ROTATE_90:
		tmp = *r;
		r->x1 = width - tmp.y2;
		r->x2 = width - tmp.y1;
		r->y1 = tmp.x1;
		r->y2 = tmp.x2;
		break;
	case DRM_MODE_ROTATE_180:
		tmp = *r;
		r->x1 = width - tmp.x2;
		r->x2 = width - tmp.x1;
		r->y1 = height - tmp.y2;
		r->y2 = height - tmp.y1;
		break;
	case DRM_MODE_ROTATE_270:
		tmp = *r;
		r->x1 = tmp.y1;
		r->x2 = tmp.y2;
		r->y1 = height - tmp.x2;
		r->y2 = height - tmp.x1;
		break;
	default:
		break;
	}

	if (rotation & (DRM_MODE_REFLECT_X | DRM_MODE_REFLECT_Y)) {
		tmp = *r;

		if (rotation & DRM_MODE_REFLECT_X) {
			r->x1 = width - tmp.x2;
			r->x2 = width - tmp.x1;
		}

		if (rotation & DRM_MODE_REFLECT_Y) {
			r->y1 = height - tmp.y2;
			r->y2 = height - tmp.y1;
		}
	}
}