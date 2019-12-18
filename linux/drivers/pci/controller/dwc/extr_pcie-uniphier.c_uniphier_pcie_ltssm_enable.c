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
struct uniphier_pcie_priv {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCL_APP_LTSSM_ENABLE ; 
 scalar_t__ PCL_APP_READY_CTRL ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void uniphier_pcie_ltssm_enable(struct uniphier_pcie_priv *priv,
				       bool enable)
{
	u32 val;

	val = readl(priv->base + PCL_APP_READY_CTRL);
	if (enable)
		val |= PCL_APP_LTSSM_ENABLE;
	else
		val &= ~PCL_APP_LTSSM_ENABLE;
	writel(val, priv->base + PCL_APP_READY_CTRL);
}