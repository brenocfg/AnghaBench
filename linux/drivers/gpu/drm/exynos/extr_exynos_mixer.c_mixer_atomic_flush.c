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
struct mixer_context {int /*<<< orphan*/  flags; } ;
struct exynos_drm_crtc {struct mixer_context* ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MXR_BIT_POWERED ; 
 int /*<<< orphan*/  exynos_crtc_handle_event (struct exynos_drm_crtc*) ; 
 int /*<<< orphan*/  mixer_enable_sync (struct mixer_context*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mixer_atomic_flush(struct exynos_drm_crtc *crtc)
{
	struct mixer_context *mixer_ctx = crtc->ctx;

	if (!test_bit(MXR_BIT_POWERED, &mixer_ctx->flags))
		return;

	mixer_enable_sync(mixer_ctx);
	exynos_crtc_handle_event(crtc);
}