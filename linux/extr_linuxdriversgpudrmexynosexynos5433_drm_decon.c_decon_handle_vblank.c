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
typedef  scalar_t__ u32 ;
struct decon_context {scalar_t__ frame_id; int /*<<< orphan*/  vblank_lock; TYPE_1__* crtc; } ;
typedef  scalar_t__ s32 ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 scalar_t__ decon_get_frame_count (struct decon_context*,int) ; 
 int /*<<< orphan*/  drm_crtc_handle_vblank (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void decon_handle_vblank(struct decon_context *ctx)
{
	u32 frm;

	spin_lock(&ctx->vblank_lock);

	frm = decon_get_frame_count(ctx, true);

	if (frm != ctx->frame_id) {
		/* handle only if incremented, take care of wrap-around */
		if ((s32)(frm - ctx->frame_id) > 0)
			drm_crtc_handle_vblank(&ctx->crtc->base);
		ctx->frame_id = frm;
	}

	spin_unlock(&ctx->vblank_lock);
}