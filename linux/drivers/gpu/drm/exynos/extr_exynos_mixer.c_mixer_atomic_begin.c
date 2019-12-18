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
struct mixer_context {int /*<<< orphan*/  dev; int /*<<< orphan*/  flags; } ;
struct exynos_drm_crtc {struct mixer_context* ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MXR_BIT_POWERED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mixer_disable_sync (struct mixer_context*) ; 
 scalar_t__ mixer_wait_for_sync (struct mixer_context*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mixer_atomic_begin(struct exynos_drm_crtc *crtc)
{
	struct mixer_context *ctx = crtc->ctx;

	if (!test_bit(MXR_BIT_POWERED, &ctx->flags))
		return;

	if (mixer_wait_for_sync(ctx))
		dev_err(ctx->dev, "timeout waiting for VSYNC\n");
	mixer_disable_sync(ctx);
}