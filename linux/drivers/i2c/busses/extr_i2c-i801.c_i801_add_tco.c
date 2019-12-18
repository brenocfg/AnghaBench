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
typedef  int /*<<< orphan*/  tco_res ;
struct resource {int start; int end; void* flags; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  bus; int /*<<< orphan*/  devfn; } ;
struct i801_priv {int features; int /*<<< orphan*/  tco_pdev; struct pci_dev* pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPIBASE ; 
 int ACPIBASE_SMI_OFF ; 
 int /*<<< orphan*/  ACPICTRL ; 
 int ACPICTRL_EN ; 
 int FEATURE_TCO_CNL ; 
 int FEATURE_TCO_SPT ; 
 size_t ICH_RES_IO_SMI ; 
 size_t ICH_RES_IO_TCO ; 
 void* IORESOURCE_IO ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 unsigned int PCI_DEVFN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PCI_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCOBASE ; 
 int /*<<< orphan*/  TCOCTL ; 
 int TCOCTL_EN ; 
 scalar_t__ acpi_has_watchdog () ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i801_add_tco_cnl (struct i801_priv*,struct pci_dev*,struct resource*) ; 
 int /*<<< orphan*/  i801_add_tco_spt (struct i801_priv*,struct pci_dev*,struct resource*) ; 
 int /*<<< orphan*/  memset (struct resource*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_bus_read_config_dword (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_bus_write_config_dword (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void i801_add_tco(struct i801_priv *priv)
{
	u32 base_addr, tco_base, tco_ctl, ctrl_val;
	struct pci_dev *pci_dev = priv->pci_dev;
	struct resource tco_res[3], *res;
	unsigned int devfn;

	/* If we have ACPI based watchdog use that instead */
	if (acpi_has_watchdog())
		return;

	if (!(priv->features & (FEATURE_TCO_SPT | FEATURE_TCO_CNL)))
		return;

	pci_read_config_dword(pci_dev, TCOBASE, &tco_base);
	pci_read_config_dword(pci_dev, TCOCTL, &tco_ctl);
	if (!(tco_ctl & TCOCTL_EN))
		return;

	memset(tco_res, 0, sizeof(tco_res));

	res = &tco_res[ICH_RES_IO_TCO];
	res->start = tco_base & ~1;
	res->end = res->start + 32 - 1;
	res->flags = IORESOURCE_IO;

	/*
	 * Power Management registers.
	 */
	devfn = PCI_DEVFN(PCI_SLOT(pci_dev->devfn), 2);
	pci_bus_read_config_dword(pci_dev->bus, devfn, ACPIBASE, &base_addr);

	res = &tco_res[ICH_RES_IO_SMI];
	res->start = (base_addr & ~1) + ACPIBASE_SMI_OFF;
	res->end = res->start + 3;
	res->flags = IORESOURCE_IO;

	/*
	 * Enable the ACPI I/O space.
	 */
	pci_bus_read_config_dword(pci_dev->bus, devfn, ACPICTRL, &ctrl_val);
	ctrl_val |= ACPICTRL_EN;
	pci_bus_write_config_dword(pci_dev->bus, devfn, ACPICTRL, ctrl_val);

	if (priv->features & FEATURE_TCO_CNL)
		priv->tco_pdev = i801_add_tco_cnl(priv, pci_dev, tco_res);
	else
		priv->tco_pdev = i801_add_tco_spt(priv, pci_dev, tco_res);

	if (IS_ERR(priv->tco_pdev))
		dev_warn(&pci_dev->dev, "failed to create iTCO device\n");
}