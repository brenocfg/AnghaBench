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
struct st_ahci_drv_data {scalar_t__ pwr; } ;
struct device {int dummy; } ;
struct ata_host {struct device* dev; struct ahci_host_priv* private_data; } ;
struct ahci_host_priv {struct st_ahci_drv_data* plat_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ahci_platform_disable_resources (struct ahci_host_priv*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int reset_control_assert (scalar_t__) ; 

__attribute__((used)) static void st_ahci_host_stop(struct ata_host *host)
{
	struct ahci_host_priv *hpriv = host->private_data;
	struct st_ahci_drv_data *drv_data = hpriv->plat_data;
	struct device *dev = host->dev;
	int err;

	if (drv_data->pwr) {
		err = reset_control_assert(drv_data->pwr);
		if (err)
			dev_err(dev, "unable to pwrdwn\n");
	}

	ahci_platform_disable_resources(hpriv);
}