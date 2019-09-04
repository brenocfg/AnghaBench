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
struct vidi_context {int /*<<< orphan*/  timer; scalar_t__ suspended; } ;
struct exynos_drm_crtc {struct vidi_context* ctx; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  VIDI_REFRESH_TIME ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidi_enable_vblank(struct exynos_drm_crtc *crtc)
{
	struct vidi_context *ctx = crtc->ctx;

	if (ctx->suspended)
		return -EPERM;

	mod_timer(&ctx->timer,
		jiffies + msecs_to_jiffies(VIDI_REFRESH_TIME) - 1);

	return 0;
}