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
typedef  int uint32_t ;
typedef  int u64 ;
struct vmw_private {scalar_t__ active_display_unit; scalar_t__ stdu_max_width; scalar_t__ stdu_max_height; int prim_bb_mem; int capabilities; } ;
struct drm_rect {scalar_t__ x2; int y2; int /*<<< orphan*/  member_0; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int SVGA_CAP_NO_BB_RESTRICTION ; 
 int /*<<< orphan*/  VMW_DEBUG_KMS (char*) ; 
 scalar_t__ drm_rect_height (struct drm_rect*) ; 
 scalar_t__ drm_rect_width (struct drm_rect*) ; 
 scalar_t__ vmw_du_screen_target ; 
 struct vmw_private* vmw_priv (struct drm_device*) ; 

__attribute__((used)) static int vmw_kms_check_display_memory(struct drm_device *dev,
					uint32_t num_rects,
					struct drm_rect *rects)
{
	struct vmw_private *dev_priv = vmw_priv(dev);
	struct drm_rect bounding_box = {0};
	u64 total_pixels = 0, pixel_mem, bb_mem;
	int i;

	for (i = 0; i < num_rects; i++) {
		/*
		 * For STDU only individual screen (screen target) is limited by
		 * SCREENTARGET_MAX_WIDTH/HEIGHT registers.
		 */
		if (dev_priv->active_display_unit == vmw_du_screen_target &&
		    (drm_rect_width(&rects[i]) > dev_priv->stdu_max_width ||
		     drm_rect_height(&rects[i]) > dev_priv->stdu_max_height)) {
			VMW_DEBUG_KMS("Screen size not supported.\n");
			return -EINVAL;
		}

		/* Bounding box upper left is at (0,0). */
		if (rects[i].x2 > bounding_box.x2)
			bounding_box.x2 = rects[i].x2;

		if (rects[i].y2 > bounding_box.y2)
			bounding_box.y2 = rects[i].y2;

		total_pixels += (u64) drm_rect_width(&rects[i]) *
			(u64) drm_rect_height(&rects[i]);
	}

	/* Virtual svga device primary limits are always in 32-bpp. */
	pixel_mem = total_pixels * 4;

	/*
	 * For HV10 and below prim_bb_mem is vram size. When
	 * SVGA_REG_MAX_PRIMARY_BOUNDING_BOX_MEM is not present vram size is
	 * limit on primary bounding box
	 */
	if (pixel_mem > dev_priv->prim_bb_mem) {
		VMW_DEBUG_KMS("Combined output size too large.\n");
		return -EINVAL;
	}

	/* SVGA_CAP_NO_BB_RESTRICTION is available for STDU only. */
	if (dev_priv->active_display_unit != vmw_du_screen_target ||
	    !(dev_priv->capabilities & SVGA_CAP_NO_BB_RESTRICTION)) {
		bb_mem = (u64) bounding_box.x2 * bounding_box.y2 * 4;

		if (bb_mem > dev_priv->prim_bb_mem) {
			VMW_DEBUG_KMS("Topology is beyond supported limits.\n");
			return -EINVAL;
		}
	}

	return 0;
}