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
struct i801_priv {int /*<<< orphan*/  tco_pdev; int /*<<< orphan*/  original_hstcfg; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMBHSTCFG ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i801_acpi_remove (struct i801_priv*) ; 
 int /*<<< orphan*/  i801_del_mux (struct i801_priv*) ; 
 int /*<<< orphan*/  i801_disable_host_notify (struct i801_priv*) ; 
 struct i801_priv* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_forbid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i801_remove(struct pci_dev *dev)
{
	struct i801_priv *priv = pci_get_drvdata(dev);

	pm_runtime_forbid(&dev->dev);
	pm_runtime_get_noresume(&dev->dev);

	i801_disable_host_notify(priv);
	i801_del_mux(priv);
	i2c_del_adapter(&priv->adapter);
	i801_acpi_remove(priv);
	pci_write_config_byte(dev, SMBHSTCFG, priv->original_hstcfg);

	platform_device_unregister(priv->tco_pdev);

	/*
	 * do not call pci_disable_device(dev) since it can cause hard hangs on
	 * some systems during power-off (eg. Fujitsu-Siemens Lifebook E8010)
	 */
}