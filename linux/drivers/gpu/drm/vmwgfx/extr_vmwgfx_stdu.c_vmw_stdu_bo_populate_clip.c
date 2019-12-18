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
struct vmw_du_update_plane {int dummy; } ;
struct drm_rect {int /*<<< orphan*/  y1; int /*<<< orphan*/  x1; } ;
struct SVGA3dCopyBox {int srcx; int srcy; int d; int /*<<< orphan*/  h; int /*<<< orphan*/  w; scalar_t__ z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; scalar_t__ srcz; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_rect_height (struct drm_rect*) ; 
 int /*<<< orphan*/  drm_rect_width (struct drm_rect*) ; 

__attribute__((used)) static uint32_t vmw_stdu_bo_populate_clip(struct vmw_du_update_plane  *update,
					  void *cmd, struct drm_rect *clip,
					  uint32_t fb_x, uint32_t fb_y)
{
	struct SVGA3dCopyBox *box = cmd;

	box->srcx = fb_x;
	box->srcy = fb_y;
	box->srcz = 0;
	box->x = clip->x1;
	box->y = clip->y1;
	box->z = 0;
	box->w = drm_rect_width(clip);
	box->h = drm_rect_height(clip);
	box->d = 1;

	return sizeof(*box);
}