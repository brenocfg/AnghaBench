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
struct pcie_port {int dummy; } ;
struct irq_data {int dummy; } ;
struct dw_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (scalar_t__) ; 
 scalar_t__ PCL_RCV_INTX ; 
 int /*<<< orphan*/  PCL_RCV_INTX_ALL_MASK ; 
 scalar_t__ PCL_RCV_INTX_MASK_SHIFT ; 
 struct pcie_port* irq_data_get_irq_chip_data (struct irq_data*) ; 
 scalar_t__ irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 struct dw_pcie* to_dw_pcie_from_pp (struct pcie_port*) ; 
 struct uniphier_pcie_priv* to_uniphier_pcie (struct dw_pcie*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void uniphier_pcie_irq_mask(struct irq_data *d)
{
	struct pcie_port *pp = irq_data_get_irq_chip_data(d);
	struct dw_pcie *pci = to_dw_pcie_from_pp(pp);
	struct uniphier_pcie_priv *priv = to_uniphier_pcie(pci);
	u32 val;

	val = readl(priv->base + PCL_RCV_INTX);
	val &= ~PCL_RCV_INTX_ALL_MASK;
	val |= BIT(irqd_to_hwirq(d) + PCL_RCV_INTX_MASK_SHIFT);
	writel(val, priv->base + PCL_RCV_INTX);
}