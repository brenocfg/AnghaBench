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
struct net_device {int /*<<< orphan*/  phydev; } ;
struct fs_enet_private {int /*<<< orphan*/  napi; int /*<<< orphan*/  interrupt; int /*<<< orphan*/  dev; int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  fs_enet_interrupt ; 
 int /*<<< orphan*/  fs_init_bds (int /*<<< orphan*/ ) ; 
 int fs_init_phy (struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct fs_enet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_start (int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct net_device*) ; 

__attribute__((used)) static int fs_enet_open(struct net_device *dev)
{
	struct fs_enet_private *fep = netdev_priv(dev);
	int r;
	int err;

	/* to initialize the fep->cur_rx,... */
	/* not doing this, will cause a crash in fs_enet_napi */
	fs_init_bds(fep->ndev);

	napi_enable(&fep->napi);

	/* Install our interrupt handler. */
	r = request_irq(fep->interrupt, fs_enet_interrupt, IRQF_SHARED,
			"fs_enet-mac", dev);
	if (r != 0) {
		dev_err(fep->dev, "Could not allocate FS_ENET IRQ!");
		napi_disable(&fep->napi);
		return -EINVAL;
	}

	err = fs_init_phy(dev);
	if (err) {
		free_irq(fep->interrupt, dev);
		napi_disable(&fep->napi);
		return err;
	}
	phy_start(dev->phydev);

	netif_start_queue(dev);

	return 0;
}