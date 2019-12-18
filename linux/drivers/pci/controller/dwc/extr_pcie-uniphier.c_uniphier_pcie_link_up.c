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
struct uniphier_pcie_priv {scalar_t__ base; } ;
struct dw_pcie {int dummy; } ;

/* Variables and functions */
 int PCL_RDLH_LINK_UP ; 
 scalar_t__ PCL_STATUS_LINK ; 
 int PCL_XMLH_LINK_UP ; 
 int readl (scalar_t__) ; 
 struct uniphier_pcie_priv* to_uniphier_pcie (struct dw_pcie*) ; 

__attribute__((used)) static int uniphier_pcie_link_up(struct dw_pcie *pci)
{
	struct uniphier_pcie_priv *priv = to_uniphier_pcie(pci);
	u32 val, mask;

	val = readl(priv->base + PCL_STATUS_LINK);
	mask = PCL_RDLH_LINK_UP | PCL_XMLH_LINK_UP;

	return (val & mask) == mask;
}