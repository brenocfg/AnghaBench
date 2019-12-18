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
typedef  int u32 ;
struct drm_display_mode {int clock; } ;
struct ade_hw_ctx {int /*<<< orphan*/  ade_pix_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int,int) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ade_set_pix_clk(struct ade_hw_ctx *ctx,
			    struct drm_display_mode *mode,
			    struct drm_display_mode *adj_mode)
{
	u32 clk_Hz = mode->clock * 1000;
	int ret;

	/*
	 * Success should be guaranteed in mode_valid call back,
	 * so failure shouldn't happen here
	 */
	ret = clk_set_rate(ctx->ade_pix_clk, clk_Hz);
	if (ret)
		DRM_ERROR("failed to set pixel clk %dHz (%d)\n", clk_Hz, ret);
	adj_mode->clock = clk_get_rate(ctx->ade_pix_clk) / 1000;
}