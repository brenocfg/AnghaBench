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
struct aspeed_gfx {scalar_t__ base; int /*<<< orphan*/  scu; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 scalar_t__ CRT_CTRL1 ; 
 scalar_t__ CRT_CTRL2 ; 
 int CRT_CTRL_DAC_EN ; 
 int CRT_CTRL_EN ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void aspeed_gfx_enable_controller(struct aspeed_gfx *priv)
{
	u32 ctrl1 = readl(priv->base + CRT_CTRL1);
	u32 ctrl2 = readl(priv->base + CRT_CTRL2);

	/* SCU2C: set DAC source for display output to Graphics CRT (GFX) */
	regmap_update_bits(priv->scu, 0x2c, BIT(16), BIT(16));

	writel(ctrl1 | CRT_CTRL_EN, priv->base + CRT_CTRL1);
	writel(ctrl2 | CRT_CTRL_DAC_EN, priv->base + CRT_CTRL2);
}