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
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __bnx2x_remove (struct pci_dev*,struct net_device*,struct bnx2x*,int) ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static void bnx2x_shutdown(struct pci_dev *pdev)
{
	struct net_device *dev = pci_get_drvdata(pdev);
	struct bnx2x *bp;

	if (!dev)
		return;

	bp = netdev_priv(dev);
	if (!bp)
		return;

	rtnl_lock();
	netif_device_detach(dev);
	rtnl_unlock();

	/* Don't remove the netdevice, as there are scenarios which will cause
	 * the kernel to hang, e.g., when trying to remove bnx2i while the
	 * rootfs is mounted from SAN.
	 */
	__bnx2x_remove(pdev, dev, bp, false);
}