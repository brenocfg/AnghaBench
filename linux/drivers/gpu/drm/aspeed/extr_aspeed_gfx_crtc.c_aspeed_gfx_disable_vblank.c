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
struct drm_simple_display_pipe {int dummy; } ;
struct aspeed_gfx {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ CRT_CTRL1 ; 
 int CRT_CTRL_VERTICAL_INTR_EN ; 
 int CRT_CTRL_VERTICAL_INTR_STS ; 
 struct aspeed_gfx* drm_pipe_to_aspeed_gfx (struct drm_simple_display_pipe*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void aspeed_gfx_disable_vblank(struct drm_simple_display_pipe *pipe)
{
	struct aspeed_gfx *priv = drm_pipe_to_aspeed_gfx(pipe);
	u32 reg = readl(priv->base + CRT_CTRL1);

	reg &= ~CRT_CTRL_VERTICAL_INTR_EN;
	writel(reg, priv->base + CRT_CTRL1);

	/* Clear pending VBLANK IRQ */
	writel(reg | CRT_CTRL_VERTICAL_INTR_STS, priv->base + CRT_CTRL1);
}