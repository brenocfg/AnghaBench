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
struct niu {int /*<<< orphan*/ * regs; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 struct niu* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  niu_ldg_free (struct niu*) ; 
 int /*<<< orphan*/  niu_put_parent (struct niu*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void niu_pci_remove_one(struct pci_dev *pdev)
{
	struct net_device *dev = pci_get_drvdata(pdev);

	if (dev) {
		struct niu *np = netdev_priv(dev);

		unregister_netdev(dev);
		if (np->regs) {
			iounmap(np->regs);
			np->regs = NULL;
		}

		niu_ldg_free(np);

		niu_put_parent(np);

		free_netdev(dev);
		pci_release_regions(pdev);
		pci_disable_device(pdev);
	}
}