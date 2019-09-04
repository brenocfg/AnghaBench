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
struct net_device {int dummy; } ;
struct jme_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  jme_powersave_phy (struct jme_adapter*) ; 
 struct jme_adapter* netdev_priv (struct net_device*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_pme_active (struct pci_dev*,int) ; 

__attribute__((used)) static void
jme_shutdown(struct pci_dev *pdev)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct jme_adapter *jme = netdev_priv(netdev);

	jme_powersave_phy(jme);
	pci_pme_active(pdev, true);
}