#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct resource {int start; scalar_t__ end; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct lpc_ich_priv {size_t chipset; int /*<<< orphan*/  gbase; int /*<<< orphan*/  abase; } ;
struct TYPE_5__ {int gpio_version; int use_gpio; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  num_resources; } ;

/* Variables and functions */
 scalar_t__ ACPIBASE_GPE_END ; 
 int ACPIBASE_GPE_OFF ; 
 int ENODEV ; 
 size_t ICH_RES_GPE0 ; 
 size_t ICH_RES_GPIO ; 
#define  ICH_V10CORP_GPIO 129 
#define  ICH_V5_GPIO 128 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int acpi_check_resource_conflict (struct resource*) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ *,char*) ; 
 struct resource* gpio_ich_res ; 
 TYPE_3__* lpc_chipset_info ; 
 int lpc_ich_check_conflict_gpio (struct resource*) ; 
 int /*<<< orphan*/  lpc_ich_enable_acpi_space (struct pci_dev*) ; 
 int /*<<< orphan*/  lpc_ich_enable_gpio_space (struct pci_dev*) ; 
 int /*<<< orphan*/  lpc_ich_finalize_gpio_cell (struct pci_dev*) ; 
 TYPE_1__ lpc_ich_gpio_cell ; 
 int mfd_add_devices (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct lpc_ich_priv* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpc_ich_init_gpio(struct pci_dev *dev)
{
	struct lpc_ich_priv *priv = pci_get_drvdata(dev);
	u32 base_addr_cfg;
	u32 base_addr;
	int ret;
	bool acpi_conflict = false;
	struct resource *res;

	/* Setup power management base register */
	pci_read_config_dword(dev, priv->abase, &base_addr_cfg);
	base_addr = base_addr_cfg & 0x0000ff80;
	if (!base_addr) {
		dev_notice(&dev->dev, "I/O space for ACPI uninitialized\n");
		lpc_ich_gpio_cell.num_resources--;
		goto gpe0_done;
	}

	res = &gpio_ich_res[ICH_RES_GPE0];
	res->start = base_addr + ACPIBASE_GPE_OFF;
	res->end = base_addr + ACPIBASE_GPE_END;
	ret = acpi_check_resource_conflict(res);
	if (ret) {
		/*
		 * This isn't fatal for the GPIO, but we have to make sure that
		 * the platform_device subsystem doesn't see this resource
		 * or it will register an invalid region.
		 */
		lpc_ich_gpio_cell.num_resources--;
		acpi_conflict = true;
	} else {
		lpc_ich_enable_acpi_space(dev);
	}

gpe0_done:
	/* Setup GPIO base register */
	pci_read_config_dword(dev, priv->gbase, &base_addr_cfg);
	base_addr = base_addr_cfg & 0x0000ff80;
	if (!base_addr) {
		dev_notice(&dev->dev, "I/O space for GPIO uninitialized\n");
		ret = -ENODEV;
		goto gpio_done;
	}

	/* Older devices provide fewer GPIO and have a smaller resource size. */
	res = &gpio_ich_res[ICH_RES_GPIO];
	res->start = base_addr;
	switch (lpc_chipset_info[priv->chipset].gpio_version) {
	case ICH_V5_GPIO:
	case ICH_V10CORP_GPIO:
		res->end = res->start + 128 - 1;
		break;
	default:
		res->end = res->start + 64 - 1;
		break;
	}

	ret = lpc_ich_check_conflict_gpio(res);
	if (ret < 0) {
		/* this isn't necessarily fatal for the GPIO */
		acpi_conflict = true;
		goto gpio_done;
	}
	lpc_chipset_info[priv->chipset].use_gpio = ret;
	lpc_ich_enable_gpio_space(dev);

	lpc_ich_finalize_gpio_cell(dev);
	ret = mfd_add_devices(&dev->dev, PLATFORM_DEVID_AUTO,
			      &lpc_ich_gpio_cell, 1, NULL, 0, NULL);

gpio_done:
	if (acpi_conflict)
		pr_warn("Resource conflict(s) found affecting %s\n",
				lpc_ich_gpio_cell.name);
	return ret;
}