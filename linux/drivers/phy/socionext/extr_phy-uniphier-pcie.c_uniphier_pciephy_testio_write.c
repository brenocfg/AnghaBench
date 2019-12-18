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
struct uniphier_pciephy_priv {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ PCL_PHY_TEST_I ; 
 scalar_t__ PCL_PHY_TEST_O ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void uniphier_pciephy_testio_write(struct uniphier_pciephy_priv *priv,
					  u32 data)
{
	/* need to read TESTO twice after accessing TESTI */
	writel(data, priv->base + PCL_PHY_TEST_I);
	readl(priv->base + PCL_PHY_TEST_O);
	readl(priv->base + PCL_PHY_TEST_O);
}