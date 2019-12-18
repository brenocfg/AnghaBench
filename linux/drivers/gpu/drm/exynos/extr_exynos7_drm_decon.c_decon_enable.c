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
struct exynos_drm_crtc {struct decon_context* ctx; } ;
struct decon_context {int suspended; int /*<<< orphan*/  crtc; int /*<<< orphan*/  irq_flags; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  decon_commit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decon_enable_vblank (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decon_init (struct decon_context*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void decon_enable(struct exynos_drm_crtc *crtc)
{
	struct decon_context *ctx = crtc->ctx;

	if (!ctx->suspended)
		return;

	pm_runtime_get_sync(ctx->dev);

	decon_init(ctx);

	/* if vblank was enabled status, enable it again. */
	if (test_and_clear_bit(0, &ctx->irq_flags))
		decon_enable_vblank(ctx->crtc);

	decon_commit(ctx->crtc);

	ctx->suspended = false;
}