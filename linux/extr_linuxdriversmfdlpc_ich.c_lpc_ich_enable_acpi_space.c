#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct pci_dev {int dummy; } ;
struct lpc_ich_priv {size_t chipset; int abase_save; int actrl_pbase_save; int /*<<< orphan*/  actrl_pbase; int /*<<< orphan*/  abase; } ;
struct TYPE_2__ {int iTCO_version; } ;

/* Variables and functions */
 TYPE_1__* lpc_chipset_info ; 
 struct lpc_ich_priv* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lpc_ich_enable_acpi_space(struct pci_dev *dev)
{
	struct lpc_ich_priv *priv = pci_get_drvdata(dev);
	u8 reg_save;

	switch (lpc_chipset_info[priv->chipset].iTCO_version) {
	case 3:
		/*
		 * Some chipsets (eg Avoton) enable the ACPI space in the
		 * ACPI BASE register.
		 */
		pci_read_config_byte(dev, priv->abase, &reg_save);
		pci_write_config_byte(dev, priv->abase, reg_save | 0x2);
		priv->abase_save = reg_save;
		break;
	default:
		/*
		 * Most chipsets enable the ACPI space in the ACPI control
		 * register.
		 */
		pci_read_config_byte(dev, priv->actrl_pbase, &reg_save);
		pci_write_config_byte(dev, priv->actrl_pbase, reg_save | 0x80);
		priv->actrl_pbase_save = reg_save;
		break;
	}
}