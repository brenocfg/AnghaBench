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
struct drm_modeset_acquire_ctx {int /*<<< orphan*/  ww_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ww_acquire_fini (int /*<<< orphan*/ *) ; 

void drm_modeset_acquire_fini(struct drm_modeset_acquire_ctx *ctx)
{
	ww_acquire_fini(&ctx->ww_ctx);
}