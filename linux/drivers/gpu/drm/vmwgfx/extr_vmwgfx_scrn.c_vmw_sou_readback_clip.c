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
struct TYPE_7__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct TYPE_6__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_8__ {TYPE_3__ srcRect; TYPE_2__ destOrigin; int /*<<< orphan*/  srcScreenId; } ;
struct vmw_kms_sou_readback_blit {TYPE_4__ body; int /*<<< orphan*/  header; } ;
struct vmw_kms_dirty {int /*<<< orphan*/  num_hits; int /*<<< orphan*/  unit_y2; int /*<<< orphan*/  unit_x2; int /*<<< orphan*/  unit_y1; int /*<<< orphan*/  unit_x1; int /*<<< orphan*/  fb_y; int /*<<< orphan*/  fb_x; TYPE_1__* unit; struct vmw_kms_sou_readback_blit* cmd; } ;
struct TYPE_5__ {int /*<<< orphan*/  unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVGA_CMD_BLIT_SCREEN_TO_GMRFB ; 

__attribute__((used)) static void vmw_sou_readback_clip(struct vmw_kms_dirty *dirty)
{
	struct vmw_kms_sou_readback_blit *blit = dirty->cmd;

	blit += dirty->num_hits;
	blit->header = SVGA_CMD_BLIT_SCREEN_TO_GMRFB;
	blit->body.srcScreenId = dirty->unit->unit;
	blit->body.destOrigin.x = dirty->fb_x;
	blit->body.destOrigin.y = dirty->fb_y;
	blit->body.srcRect.left = dirty->unit_x1;
	blit->body.srcRect.top = dirty->unit_y1;
	blit->body.srcRect.right = dirty->unit_x2;
	blit->body.srcRect.bottom = dirty->unit_y2;
	dirty->num_hits++;
}