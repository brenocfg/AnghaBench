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
struct vidi_context {int /*<<< orphan*/  timer; TYPE_1__* crtc; } ;
struct timer_list {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIDI_REFRESH_TIME ; 
 struct vidi_context* ctx ; 
 scalar_t__ drm_crtc_handle_vblank (int /*<<< orphan*/ *) ; 
 struct vidi_context* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void vidi_fake_vblank_timer(struct timer_list *t)
{
	struct vidi_context *ctx = from_timer(ctx, t, timer);

	if (drm_crtc_handle_vblank(&ctx->crtc->base))
		mod_timer(&ctx->timer,
			jiffies + msecs_to_jiffies(VIDI_REFRESH_TIME) - 1);
}