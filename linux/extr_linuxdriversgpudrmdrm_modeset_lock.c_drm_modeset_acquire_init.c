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
struct drm_modeset_acquire_ctx {int interruptible; int /*<<< orphan*/  locked; int /*<<< orphan*/  ww_ctx; } ;

/* Variables and functions */
 int DRM_MODESET_ACQUIRE_INTERRUPTIBLE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crtc_ww_class ; 
 int /*<<< orphan*/  memset (struct drm_modeset_acquire_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ww_acquire_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void drm_modeset_acquire_init(struct drm_modeset_acquire_ctx *ctx,
		uint32_t flags)
{
	memset(ctx, 0, sizeof(*ctx));
	ww_acquire_init(&ctx->ww_ctx, &crtc_ww_class);
	INIT_LIST_HEAD(&ctx->locked);

	if (flags & DRM_MODESET_ACQUIRE_INTERRUPTIBLE)
		ctx->interruptible = true;
}