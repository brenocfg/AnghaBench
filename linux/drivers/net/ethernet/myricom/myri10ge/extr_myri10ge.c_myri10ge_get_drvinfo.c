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
struct net_device {int dummy; } ;
struct myri10ge_priv {char* fw_version; int /*<<< orphan*/  pdev; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 char* MYRI10GE_VERSION_STR ; 
 struct myri10ge_priv* netdev_priv (struct net_device*) ; 
 char* pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
myri10ge_get_drvinfo(struct net_device *netdev, struct ethtool_drvinfo *info)
{
	struct myri10ge_priv *mgp = netdev_priv(netdev);

	strlcpy(info->driver, "myri10ge", sizeof(info->driver));
	strlcpy(info->version, MYRI10GE_VERSION_STR, sizeof(info->version));
	strlcpy(info->fw_version, mgp->fw_version, sizeof(info->fw_version));
	strlcpy(info->bus_info, pci_name(mgp->pdev), sizeof(info->bus_info));
}