#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  name; } ;
struct gem {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  gem_clean_rings (struct gem*) ; 
 int /*<<< orphan*/  gem_get_cell (struct gem*) ; 
 int /*<<< orphan*/  gem_init_phy (struct gem*) ; 
 int /*<<< orphan*/  gem_interrupt ; 
 int /*<<< orphan*/  gem_netif_start (struct gem*) ; 
 int /*<<< orphan*/  gem_put_cell (struct gem*) ; 
 int /*<<< orphan*/  gem_reinit_chip (struct gem*) ; 
 int /*<<< orphan*/  gem_reset (struct gem*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct gem* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 int pci_enable_device (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_set_master (TYPE_1__*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int gem_do_start(struct net_device *dev)
{
	struct gem *gp = netdev_priv(dev);
	int rc;

	/* Enable the cell */
	gem_get_cell(gp);

	/* Make sure PCI access and bus master are enabled */
	rc = pci_enable_device(gp->pdev);
	if (rc) {
		netdev_err(dev, "Failed to enable chip on PCI bus !\n");

		/* Put cell and forget it for now, it will be considered as
		 * still asleep, a new sleep cycle may bring it back
		 */
		gem_put_cell(gp);
		return -ENXIO;
	}
	pci_set_master(gp->pdev);

	/* Init & setup chip hardware */
	gem_reinit_chip(gp);

	/* An interrupt might come in handy */
	rc = request_irq(gp->pdev->irq, gem_interrupt,
			 IRQF_SHARED, dev->name, (void *)dev);
	if (rc) {
		netdev_err(dev, "failed to request irq !\n");

		gem_reset(gp);
		gem_clean_rings(gp);
		gem_put_cell(gp);
		return rc;
	}

	/* Mark us as attached again if we come from resume(), this has
	 * no effect if we weren't detached and needs to be done now.
	 */
	netif_device_attach(dev);

	/* Restart NAPI & queues */
	gem_netif_start(gp);

	/* Detect & init PHY, start autoneg etc... this will
	 * eventually result in starting DMA operations when
	 * the link is up
	 */
	gem_init_phy(gp);

	return 0;
}