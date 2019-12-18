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
struct pcie_port {int dummy; } ;
struct dw_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PCI_MSI ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_pcie_msi_init (struct pcie_port*) ; 
 int /*<<< orphan*/  dw_pcie_setup_rc (struct pcie_port*) ; 
 struct dw_pcie* to_dw_pcie_from_pp (struct pcie_port*) ; 
 struct uniphier_pcie_priv* to_uniphier_pcie (struct dw_pcie*) ; 
 int uniphier_pcie_config_legacy_irq (struct pcie_port*) ; 
 int uniphier_pcie_establish_link (struct dw_pcie*) ; 
 int /*<<< orphan*/  uniphier_pcie_irq_enable (struct uniphier_pcie_priv*) ; 

__attribute__((used)) static int uniphier_pcie_host_init(struct pcie_port *pp)
{
	struct dw_pcie *pci = to_dw_pcie_from_pp(pp);
	struct uniphier_pcie_priv *priv = to_uniphier_pcie(pci);
	int ret;

	ret = uniphier_pcie_config_legacy_irq(pp);
	if (ret)
		return ret;

	uniphier_pcie_irq_enable(priv);

	dw_pcie_setup_rc(pp);
	ret = uniphier_pcie_establish_link(pci);
	if (ret)
		return ret;

	if (IS_ENABLED(CONFIG_PCI_MSI))
		dw_pcie_msi_init(pp);

	return 0;
}