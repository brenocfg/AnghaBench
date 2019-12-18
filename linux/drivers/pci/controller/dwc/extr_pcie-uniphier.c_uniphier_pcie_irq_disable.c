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
struct uniphier_pcie_priv {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ PCL_RCV_INT ; 
 scalar_t__ PCL_RCV_INTX ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void uniphier_pcie_irq_disable(struct uniphier_pcie_priv *priv)
{
	writel(0, priv->base + PCL_RCV_INT);
	writel(0, priv->base + PCL_RCV_INTX);
}