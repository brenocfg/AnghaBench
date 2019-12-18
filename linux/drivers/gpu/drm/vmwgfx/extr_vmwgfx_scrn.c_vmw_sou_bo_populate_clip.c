#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct TYPE_6__ {int x; int y; } ;
struct TYPE_8__ {TYPE_3__ destRect; TYPE_2__ srcOrigin; int /*<<< orphan*/  destScreenId; } ;
struct vmw_kms_sou_bo_blit {TYPE_4__ body; int /*<<< orphan*/  header; } ;
struct vmw_du_update_plane {TYPE_1__* du; } ;
struct drm_rect {int /*<<< orphan*/  y2; int /*<<< orphan*/  x2; int /*<<< orphan*/  y1; int /*<<< orphan*/  x1; } ;
struct TYPE_5__ {int /*<<< orphan*/  unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVGA_CMD_BLIT_GMRFB_TO_SCREEN ; 

__attribute__((used)) static uint32_t vmw_sou_bo_populate_clip(struct vmw_du_update_plane  *update,
					 void *cmd, struct drm_rect *clip,
					 uint32_t fb_x, uint32_t fb_y)
{
	struct vmw_kms_sou_bo_blit *blit = cmd;

	blit->header = SVGA_CMD_BLIT_GMRFB_TO_SCREEN;
	blit->body.destScreenId = update->du->unit;
	blit->body.srcOrigin.x = fb_x;
	blit->body.srcOrigin.y = fb_y;
	blit->body.destRect.left = clip->x1;
	blit->body.destRect.top = clip->y1;
	blit->body.destRect.right = clip->x2;
	blit->body.destRect.bottom = clip->y2;

	return sizeof(*blit);
}