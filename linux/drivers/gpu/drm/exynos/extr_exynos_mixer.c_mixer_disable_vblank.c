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
 int /*<<< orphan*/  MXR_BIT_VSYNC ; 
 int /*<<< orphan*/  MXR_INT_CLEAR_VSYNC ; 
 int /*<<< orphan*/  MXR_INT_EN ; 
 int /*<<< orphan*/  MXR_INT_EN_VSYNC ; 
 int /*<<< orphan*/  MXR_INT_STATUS ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mixer_reg_writemask (struct mixer_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mixer_disable_vblank(struct exynos_drm_crtc *crtc)
{
	struct mixer_context *mixer_ctx = crtc->ctx;

	__clear_bit(MXR_BIT_VSYNC, &mixer_ctx->flags);

	if (!test_bit(MXR_BIT_POWERED, &mixer_ctx->flags))
		return;

	/* disable vsync interrupt */
	mixer_reg_writemask(mixer_ctx, MXR_INT_STATUS, ~0, MXR_INT_CLEAR_VSYNC);
	mixer_reg_writemask(mixer_ctx, MXR_INT_EN, 0, MXR_INT_EN_VSYNC);
}