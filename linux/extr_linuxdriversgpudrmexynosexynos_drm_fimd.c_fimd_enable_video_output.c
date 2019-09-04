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
typedef  int /*<<< orphan*/  u32 ;
struct fimd_context {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ WINCON (unsigned int) ; 
 int /*<<< orphan*/  WINCONx_ENWIN ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void fimd_enable_video_output(struct fimd_context *ctx, unsigned int win,
					bool enable)
{
	u32 val = readl(ctx->regs + WINCON(win));

	if (enable)
		val |= WINCONx_ENWIN;
	else
		val &= ~WINCONx_ENWIN;

	writel(val, ctx->regs + WINCON(win));
}