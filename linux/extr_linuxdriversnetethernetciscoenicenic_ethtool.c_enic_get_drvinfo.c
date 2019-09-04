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
struct vnic_devcmd_fw_info {int /*<<< orphan*/  fw_version; } ;
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;
struct enic {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  DRV_VERSION ; 
 int ENOMEM ; 
 int enic_dev_fw_info (struct enic*,struct vnic_devcmd_fw_info**) ; 
 struct enic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void enic_get_drvinfo(struct net_device *netdev,
	struct ethtool_drvinfo *drvinfo)
{
	struct enic *enic = netdev_priv(netdev);
	struct vnic_devcmd_fw_info *fw_info;
	int err;

	err = enic_dev_fw_info(enic, &fw_info);
	/* return only when pci_zalloc_consistent fails in vnic_dev_fw_info
	 * For other failures, like devcmd failure, we return previously
	 * recorded info.
	 */
	if (err == -ENOMEM)
		return;

	strlcpy(drvinfo->driver, DRV_NAME, sizeof(drvinfo->driver));
	strlcpy(drvinfo->version, DRV_VERSION, sizeof(drvinfo->version));
	strlcpy(drvinfo->fw_version, fw_info->fw_version,
		sizeof(drvinfo->fw_version));
	strlcpy(drvinfo->bus_info, pci_name(enic->pdev),
		sizeof(drvinfo->bus_info));
}