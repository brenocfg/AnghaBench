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
struct ade_hw_ctx {int power_on; int /*<<< orphan*/  ade_core_clk; int /*<<< orphan*/  reset; int /*<<< orphan*/  media_noc_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  ade_init (struct ade_hw_ctx*) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ade_power_up(struct ade_hw_ctx *ctx)
{
	int ret;

	ret = clk_prepare_enable(ctx->media_noc_clk);
	if (ret) {
		DRM_ERROR("failed to enable media_noc_clk (%d)\n", ret);
		return ret;
	}

	ret = reset_control_deassert(ctx->reset);
	if (ret) {
		DRM_ERROR("failed to deassert reset\n");
		return ret;
	}

	ret = clk_prepare_enable(ctx->ade_core_clk);
	if (ret) {
		DRM_ERROR("failed to enable ade_core_clk (%d)\n", ret);
		return ret;
	}

	ade_init(ctx);
	ctx->power_on = true;
	return 0;
}