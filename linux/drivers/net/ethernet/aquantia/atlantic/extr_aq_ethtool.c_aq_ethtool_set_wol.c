#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct ethtool_wolinfo {int wolopts; } ;
struct aq_nic_s {int dummy; } ;
struct aq_nic_cfg_s {int /*<<< orphan*/  wol; } ;

/* Variables and functions */
 int /*<<< orphan*/  AQ_NIC_WOL_ENABLED ; 
 int WAKE_MAGIC ; 
 struct aq_nic_cfg_s* aq_nic_get_cfg (struct aq_nic_s*) ; 
 int device_set_wakeup_enable (int /*<<< orphan*/ *,int) ; 
 struct aq_nic_s* netdev_priv (struct net_device*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aq_ethtool_set_wol(struct net_device *ndev,
			      struct ethtool_wolinfo *wol)
{
	struct pci_dev *pdev = to_pci_dev(ndev->dev.parent);
	struct aq_nic_s *aq_nic = netdev_priv(ndev);
	struct aq_nic_cfg_s *cfg = aq_nic_get_cfg(aq_nic);
	int err = 0;

	if (wol->wolopts & WAKE_MAGIC)
		cfg->wol |= AQ_NIC_WOL_ENABLED;
	else
		cfg->wol &= ~AQ_NIC_WOL_ENABLED;
	err = device_set_wakeup_enable(&pdev->dev, wol->wolopts);

	return err;
}