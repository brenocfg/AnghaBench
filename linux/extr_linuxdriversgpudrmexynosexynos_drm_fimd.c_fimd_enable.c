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
struct fimd_context {int suspended; int /*<<< orphan*/  crtc; int /*<<< orphan*/  irq_flags; int /*<<< orphan*/  dev; } ;
struct exynos_drm_crtc {struct fimd_context* ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  fimd_commit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimd_enable_vblank (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fimd_enable(struct exynos_drm_crtc *crtc)
{
	struct fimd_context *ctx = crtc->ctx;

	if (!ctx->suspended)
		return;

	ctx->suspended = false;

	pm_runtime_get_sync(ctx->dev);

	/* if vblank was enabled status, enable it again. */
	if (test_and_clear_bit(0, &ctx->irq_flags))
		fimd_enable_vblank(ctx->crtc);

	fimd_commit(ctx->crtc);
}