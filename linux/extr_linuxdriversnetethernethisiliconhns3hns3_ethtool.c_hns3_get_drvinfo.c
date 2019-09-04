#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct hns3_nic_priv {struct hnae3_handle* ae_handle; } ;
struct hnae3_handle {TYPE_3__* ae_algo; TYPE_4__* pdev; } ;
struct ethtool_drvinfo {char* version; char* driver; char* bus_info; int /*<<< orphan*/  fw_version; } ;
struct TYPE_8__ {TYPE_1__* driver; } ;
struct TYPE_7__ {TYPE_2__* ops; } ;
struct TYPE_6__ {int (* get_fw_version ) (struct hnae3_handle*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ETHTOOL_BUSINFO_LEN ; 
 int /*<<< orphan*/  hns3_driver_version ; 
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_name (TYPE_4__*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct hnae3_handle*) ; 
 int stub2 (struct hnae3_handle*) ; 

__attribute__((used)) static void hns3_get_drvinfo(struct net_device *netdev,
			     struct ethtool_drvinfo *drvinfo)
{
	struct hns3_nic_priv *priv = netdev_priv(netdev);
	struct hnae3_handle *h = priv->ae_handle;

	strncpy(drvinfo->version, hns3_driver_version,
		sizeof(drvinfo->version));
	drvinfo->version[sizeof(drvinfo->version) - 1] = '\0';

	strncpy(drvinfo->driver, h->pdev->driver->name,
		sizeof(drvinfo->driver));
	drvinfo->driver[sizeof(drvinfo->driver) - 1] = '\0';

	strncpy(drvinfo->bus_info, pci_name(h->pdev),
		sizeof(drvinfo->bus_info));
	drvinfo->bus_info[ETHTOOL_BUSINFO_LEN - 1] = '\0';

	snprintf(drvinfo->fw_version, sizeof(drvinfo->fw_version), "0x%08x",
		 priv->ae_handle->ae_algo->ops->get_fw_version(h));
}