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
struct drm_display_mode {unsigned long htotal; unsigned long vtotal; unsigned long vrefresh; } ;
struct decon_context {int /*<<< orphan*/  vclk; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 decon_calc_clkdiv(struct decon_context *ctx,
		const struct drm_display_mode *mode)
{
	unsigned long ideal_clk = mode->htotal * mode->vtotal * mode->vrefresh;
	u32 clkdiv;

	/* Find the clock divider value that gets us closest to ideal_clk */
	clkdiv = DIV_ROUND_UP(clk_get_rate(ctx->vclk), ideal_clk);

	return (clkdiv < 0x100) ? clkdiv : 0xff;
}