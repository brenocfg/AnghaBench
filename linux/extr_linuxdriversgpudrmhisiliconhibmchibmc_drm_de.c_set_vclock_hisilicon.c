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
typedef  unsigned long u32 ;
struct hibmc_drm_private {scalar_t__ mmio; } ;
struct drm_device {struct hibmc_drm_private* dev_private; } ;

/* Variables and functions */
 scalar_t__ CRT_PLL1_HS ; 
 unsigned long CRT_PLL1_HS_INTER_BYPASS (int) ; 
 unsigned long CRT_PLL1_HS_OUTER_BYPASS (int) ; 
 unsigned long CRT_PLL1_HS_POWERON (int) ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static void set_vclock_hisilicon(struct drm_device *dev, unsigned long pll)
{
	u32 val;
	struct hibmc_drm_private *priv = dev->dev_private;

	val = readl(priv->mmio + CRT_PLL1_HS);
	val &= ~(CRT_PLL1_HS_OUTER_BYPASS(1));
	writel(val, priv->mmio + CRT_PLL1_HS);

	val = CRT_PLL1_HS_INTER_BYPASS(1) | CRT_PLL1_HS_POWERON(1);
	writel(val, priv->mmio + CRT_PLL1_HS);

	writel(pll, priv->mmio + CRT_PLL1_HS);

	usleep_range(1000, 2000);

	val = pll & ~(CRT_PLL1_HS_POWERON(1));
	writel(val, priv->mmio + CRT_PLL1_HS);

	usleep_range(1000, 2000);

	val &= ~(CRT_PLL1_HS_INTER_BYPASS(1));
	writel(val, priv->mmio + CRT_PLL1_HS);

	usleep_range(1000, 2000);

	val |= CRT_PLL1_HS_OUTER_BYPASS(1);
	writel(val, priv->mmio + CRT_PLL1_HS);
}