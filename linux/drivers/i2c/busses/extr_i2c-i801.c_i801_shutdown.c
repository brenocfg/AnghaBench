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
struct pci_dev {int dummy; } ;
struct i801_priv {int /*<<< orphan*/  original_hstcfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMBHSTCFG ; 
 int /*<<< orphan*/  i801_disable_host_notify (struct i801_priv*) ; 
 struct i801_priv* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i801_shutdown(struct pci_dev *dev)
{
	struct i801_priv *priv = pci_get_drvdata(dev);

	/* Restore config registers to avoid hard hang on some systems */
	i801_disable_host_notify(priv);
	pci_write_config_byte(dev, SMBHSTCFG, priv->original_hstcfg);
}