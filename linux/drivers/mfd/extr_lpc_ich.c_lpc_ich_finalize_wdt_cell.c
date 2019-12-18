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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct mfd_cell {int pdata_size; struct itco_wdt_platform_data* platform_data; } ;
struct lpc_ich_priv {size_t chipset; } ;
struct lpc_ich_info {int /*<<< orphan*/  name; int /*<<< orphan*/  iTCO_version; } ;
struct itco_wdt_platform_data {int /*<<< orphan*/  name; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct itco_wdt_platform_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct lpc_ich_info* lpc_chipset_info ; 
 struct mfd_cell lpc_ich_wdt_cell ; 
 struct lpc_ich_priv* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lpc_ich_finalize_wdt_cell(struct pci_dev *dev)
{
	struct itco_wdt_platform_data *pdata;
	struct lpc_ich_priv *priv = pci_get_drvdata(dev);
	struct lpc_ich_info *info;
	struct mfd_cell *cell = &lpc_ich_wdt_cell;

	pdata = devm_kzalloc(&dev->dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return -ENOMEM;

	info = &lpc_chipset_info[priv->chipset];

	pdata->version = info->iTCO_version;
	strlcpy(pdata->name, info->name, sizeof(pdata->name));

	cell->platform_data = pdata;
	cell->pdata_size = sizeof(*pdata);
	return 0;
}