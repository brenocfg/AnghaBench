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
struct pci_device_id {size_t driver_data; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct lpc_ich_priv {size_t chipset; int actrl_pbase_save; int abase_save; int gctrl_save; int /*<<< orphan*/  gctrl; int /*<<< orphan*/  gbase; int /*<<< orphan*/  actrl_pbase; int /*<<< orphan*/  abase; } ;
struct TYPE_2__ {scalar_t__ spi_type; scalar_t__ gpio_version; scalar_t__ iTCO_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPIBASE ; 
 int /*<<< orphan*/  ACPICTRL_PMCBASE ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOBASE_ICH0 ; 
 int /*<<< orphan*/  GPIOBASE_ICH6 ; 
 int /*<<< orphan*/  GPIOCTRL_ICH0 ; 
 int /*<<< orphan*/  GPIOCTRL_ICH6 ; 
 size_t LPC_ICH5 ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct lpc_ich_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* lpc_chipset_info ; 
 int lpc_ich_init_gpio (struct pci_dev*) ; 
 int lpc_ich_init_spi (struct pci_dev*) ; 
 int lpc_ich_init_wdt (struct pci_dev*) ; 
 int /*<<< orphan*/  lpc_ich_restore_config_space (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct lpc_ich_priv*) ; 

__attribute__((used)) static int lpc_ich_probe(struct pci_dev *dev,
				const struct pci_device_id *id)
{
	struct lpc_ich_priv *priv;
	int ret;
	bool cell_added = false;

	priv = devm_kzalloc(&dev->dev,
			    sizeof(struct lpc_ich_priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->chipset = id->driver_data;

	priv->actrl_pbase_save = -1;
	priv->abase_save = -1;

	priv->abase = ACPIBASE;
	priv->actrl_pbase = ACPICTRL_PMCBASE;

	priv->gctrl_save = -1;
	if (priv->chipset <= LPC_ICH5) {
		priv->gbase = GPIOBASE_ICH0;
		priv->gctrl = GPIOCTRL_ICH0;
	} else {
		priv->gbase = GPIOBASE_ICH6;
		priv->gctrl = GPIOCTRL_ICH6;
	}

	pci_set_drvdata(dev, priv);

	if (lpc_chipset_info[priv->chipset].iTCO_version) {
		ret = lpc_ich_init_wdt(dev);
		if (!ret)
			cell_added = true;
	}

	if (lpc_chipset_info[priv->chipset].gpio_version) {
		ret = lpc_ich_init_gpio(dev);
		if (!ret)
			cell_added = true;
	}

	if (lpc_chipset_info[priv->chipset].spi_type) {
		ret = lpc_ich_init_spi(dev);
		if (!ret)
			cell_added = true;
	}

	/*
	 * We only care if at least one or none of the cells registered
	 * successfully.
	 */
	if (!cell_added) {
		dev_warn(&dev->dev, "No MFD cells added\n");
		lpc_ich_restore_config_space(dev);
		return -ENODEV;
	}

	return 0;
}