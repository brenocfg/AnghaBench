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
struct tg3 {int /*<<< orphan*/ * regs; int /*<<< orphan*/ * aperegs; int /*<<< orphan*/  fw; } ;
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USE_PHYLIB ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 struct tg3* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ ) ; 
 scalar_t__ tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_mdio_fini (struct tg3*) ; 
 int /*<<< orphan*/  tg3_phy_fini (struct tg3*) ; 
 int /*<<< orphan*/  tg3_ptp_fini (struct tg3*) ; 
 int /*<<< orphan*/  tg3_reset_task_cancel (struct tg3*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void tg3_remove_one(struct pci_dev *pdev)
{
	struct net_device *dev = pci_get_drvdata(pdev);

	if (dev) {
		struct tg3 *tp = netdev_priv(dev);

		tg3_ptp_fini(tp);

		release_firmware(tp->fw);

		tg3_reset_task_cancel(tp);

		if (tg3_flag(tp, USE_PHYLIB)) {
			tg3_phy_fini(tp);
			tg3_mdio_fini(tp);
		}

		unregister_netdev(dev);
		if (tp->aperegs) {
			iounmap(tp->aperegs);
			tp->aperegs = NULL;
		}
		if (tp->regs) {
			iounmap(tp->regs);
			tp->regs = NULL;
		}
		free_netdev(dev);
		pci_release_regions(pdev);
		pci_disable_device(pdev);
	}
}