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
struct net_device {int dummy; } ;
struct alx_priv {struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  alx_activate (struct alx_priv*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 struct alx_priv* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static void alx_pci_error_resume(struct pci_dev *pdev)
{
	struct alx_priv *alx = pci_get_drvdata(pdev);
	struct net_device *netdev = alx->dev;

	dev_info(&pdev->dev, "pci error resume\n");

	rtnl_lock();

	if (netif_running(netdev)) {
		alx_activate(alx);
		netif_device_attach(netdev);
	}

	rtnl_unlock();
}