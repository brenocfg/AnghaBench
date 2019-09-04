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
typedef  void* u32 ;
struct drm_clip_rect {void* x1; void* x2; void* y1; void* y2; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,void*,void*,void*,void*) ; 
 unsigned int DRM_MODE_FB_DIRTY_ANNOTATE_COPY ; 
 void* max (void*,void*) ; 
 void* min (void*,void*) ; 

bool tinydrm_merge_clips(struct drm_clip_rect *dst,
			 struct drm_clip_rect *src, unsigned int num_clips,
			 unsigned int flags, u32 max_width, u32 max_height)
{
	unsigned int i;

	if (!src || !num_clips) {
		dst->x1 = 0;
		dst->x2 = max_width;
		dst->y1 = 0;
		dst->y2 = max_height;
		return true;
	}

	dst->x1 = ~0;
	dst->y1 = ~0;
	dst->x2 = 0;
	dst->y2 = 0;

	for (i = 0; i < num_clips; i++) {
		if (flags & DRM_MODE_FB_DIRTY_ANNOTATE_COPY)
			i++;
		dst->x1 = min(dst->x1, src[i].x1);
		dst->x2 = max(dst->x2, src[i].x2);
		dst->y1 = min(dst->y1, src[i].y1);
		dst->y2 = max(dst->y2, src[i].y2);
	}

	if (dst->x2 > max_width || dst->y2 > max_height ||
	    dst->x1 >= dst->x2 || dst->y1 >= dst->y2) {
		DRM_DEBUG_KMS("Illegal clip: x1=%u, x2=%u, y1=%u, y2=%u\n",
			      dst->x1, dst->x2, dst->y1, dst->y2);
		dst->x1 = 0;
		dst->y1 = 0;
		dst->x2 = max_width;
		dst->y2 = max_height;
	}

	return (dst->x2 - dst->x1) == max_width &&
	       (dst->y2 - dst->y1) == max_height;
}