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
struct rtl8169_private {TYPE_2__* phydev; int /*<<< orphan*/  napi; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int /*<<< orphan*/  perm_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  bus; } ;
struct TYPE_4__ {TYPE_1__ mdio; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 
 struct rtl8169_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 scalar_t__ pci_dev_run_wake (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (int /*<<< orphan*/ *) ; 
 scalar_t__ r8168_check_dash (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8168_driver_stop (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_rar_set (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_release_firmware (struct rtl8169_private*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void rtl_remove_one(struct pci_dev *pdev)
{
	struct net_device *dev = pci_get_drvdata(pdev);
	struct rtl8169_private *tp = netdev_priv(dev);

	if (r8168_check_dash(tp))
		rtl8168_driver_stop(tp);

	netif_napi_del(&tp->napi);

	unregister_netdev(dev);
	mdiobus_unregister(tp->phydev->mdio.bus);

	rtl_release_firmware(tp);

	if (pci_dev_run_wake(pdev))
		pm_runtime_get_noresume(&pdev->dev);

	/* restore original MAC address */
	rtl_rar_set(tp, dev->perm_addr);
}