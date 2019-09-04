#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int fw_major; int fw_minor; int fw_rev; int fw_eng; int mfw_rev; } ;
struct TYPE_4__ {TYPE_1__ common; } ;
struct qede_dev {int /*<<< orphan*/  pdev; TYPE_2__ dev_info; } ;
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 char* DRV_MODULE_VERSION ; 
 int ETHTOOL_FWVERS_LEN ; 
 struct qede_dev* netdev_priv (struct net_device*) ; 
 char* pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static void qede_get_drvinfo(struct net_device *ndev,
			     struct ethtool_drvinfo *info)
{
	char mfw[ETHTOOL_FWVERS_LEN], storm[ETHTOOL_FWVERS_LEN];
	struct qede_dev *edev = netdev_priv(ndev);

	strlcpy(info->driver, "qede", sizeof(info->driver));
	strlcpy(info->version, DRV_MODULE_VERSION, sizeof(info->version));

	snprintf(storm, ETHTOOL_FWVERS_LEN, "%d.%d.%d.%d",
		 edev->dev_info.common.fw_major,
		 edev->dev_info.common.fw_minor,
		 edev->dev_info.common.fw_rev,
		 edev->dev_info.common.fw_eng);

	snprintf(mfw, ETHTOOL_FWVERS_LEN, "%d.%d.%d.%d",
		 (edev->dev_info.common.mfw_rev >> 24) & 0xFF,
		 (edev->dev_info.common.mfw_rev >> 16) & 0xFF,
		 (edev->dev_info.common.mfw_rev >> 8) & 0xFF,
		 edev->dev_info.common.mfw_rev & 0xFF);

	if ((strlen(storm) + strlen(mfw) + strlen("mfw storm  ")) <
	    sizeof(info->fw_version)) {
		snprintf(info->fw_version, sizeof(info->fw_version),
			 "mfw %s storm %s", mfw, storm);
	} else {
		snprintf(info->fw_version, sizeof(info->fw_version),
			 "%s %s", mfw, storm);
	}

	strlcpy(info->bus_info, pci_name(edev->pdev), sizeof(info->bus_info));
}