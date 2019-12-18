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
struct decon_context {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ SHADOWCON ; 
 int /*<<< orphan*/  SHADOWCON_WINx_PROTECT (unsigned int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void decon_shadow_protect_win(struct decon_context *ctx,
				     unsigned int win, bool protect)
{
	u32 bits, val;

	bits = SHADOWCON_WINx_PROTECT(win);

	val = readl(ctx->regs + SHADOWCON);
	if (protect)
		val |= bits;
	else
		val &= ~bits;
	writel(val, ctx->regs + SHADOWCON);
}