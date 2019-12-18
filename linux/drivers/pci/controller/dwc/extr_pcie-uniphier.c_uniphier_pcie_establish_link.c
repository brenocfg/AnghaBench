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
struct uniphier_pcie_priv {int dummy; } ;
struct dw_pcie {int dummy; } ;

/* Variables and functions */
 scalar_t__ dw_pcie_link_up (struct dw_pcie*) ; 
 int dw_pcie_wait_for_link (struct dw_pcie*) ; 
 struct uniphier_pcie_priv* to_uniphier_pcie (struct dw_pcie*) ; 
 int /*<<< orphan*/  uniphier_pcie_ltssm_enable (struct uniphier_pcie_priv*,int) ; 

__attribute__((used)) static int uniphier_pcie_establish_link(struct dw_pcie *pci)
{
	struct uniphier_pcie_priv *priv = to_uniphier_pcie(pci);

	if (dw_pcie_link_up(pci))
		return 0;

	uniphier_pcie_ltssm_enable(priv, true);

	return dw_pcie_wait_for_link(pci);
}