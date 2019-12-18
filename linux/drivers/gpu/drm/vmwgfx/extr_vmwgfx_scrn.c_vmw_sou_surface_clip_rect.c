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
typedef  int uint32_t ;
struct vmw_du_update_plane {int dummy; } ;
struct drm_rect {int /*<<< orphan*/  y2; int /*<<< orphan*/  x2; int /*<<< orphan*/  y1; int /*<<< orphan*/  x1; } ;
struct TYPE_2__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
typedef  TYPE_1__ SVGASignedRect ;

/* Variables and functions */

__attribute__((used)) static uint32_t vmw_sou_surface_clip_rect(struct vmw_du_update_plane *update,
					  void *cmd, struct drm_rect *clip,
					  uint32_t src_x, uint32_t src_y)
{
	SVGASignedRect *rect = cmd;

	/*
	 * rects are relative to dest bounding box rect on screen object, so
	 * translate to it later in post_clip
	 */
	rect->left = clip->x1;
	rect->top = clip->y1;
	rect->right = clip->x2;
	rect->bottom = clip->y2;

	return sizeof(*rect);
}