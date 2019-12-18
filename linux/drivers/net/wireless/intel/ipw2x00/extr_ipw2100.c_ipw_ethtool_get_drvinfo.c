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
typedef  int /*<<< orphan*/  ucode_ver ;
struct net_device {int dummy; } ;
struct ipw2100_priv {int eeprom_version; int /*<<< orphan*/  pci_dev; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;
typedef  int /*<<< orphan*/  fw_ver ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  DRV_VERSION ; 
 int /*<<< orphan*/  ipw2100_get_fwversion (struct ipw2100_priv*,char*,int) ; 
 int /*<<< orphan*/  ipw2100_get_ucodeversion (struct ipw2100_priv*,char*,int) ; 
 struct ipw2100_priv* libipw_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ipw_ethtool_get_drvinfo(struct net_device *dev,
				    struct ethtool_drvinfo *info)
{
	struct ipw2100_priv *priv = libipw_priv(dev);
	char fw_ver[64], ucode_ver[64];

	strlcpy(info->driver, DRV_NAME, sizeof(info->driver));
	strlcpy(info->version, DRV_VERSION, sizeof(info->version));

	ipw2100_get_fwversion(priv, fw_ver, sizeof(fw_ver));
	ipw2100_get_ucodeversion(priv, ucode_ver, sizeof(ucode_ver));

	snprintf(info->fw_version, sizeof(info->fw_version), "%s:%d:%s",
		 fw_ver, priv->eeprom_version, ucode_ver);

	strlcpy(info->bus_info, pci_name(priv->pci_dev),
		sizeof(info->bus_info));
}