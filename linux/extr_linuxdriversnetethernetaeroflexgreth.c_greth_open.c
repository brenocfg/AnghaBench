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
struct net_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct greth_private {int /*<<< orphan*/  napi; TYPE_1__* regs; int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRETH_REGSAVE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  greth_clean_rings (struct greth_private*) ; 
 int /*<<< orphan*/  greth_enable_irqs (struct greth_private*) ; 
 int /*<<< orphan*/  greth_enable_rx (struct greth_private*) ; 
 int /*<<< orphan*/  greth_enable_tx (struct greth_private*) ; 
 int greth_init_rings (struct greth_private*) ; 
 int /*<<< orphan*/  greth_interrupt ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct greth_private* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_ifup (struct greth_private*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*) ; 

__attribute__((used)) static int greth_open(struct net_device *dev)
{
	struct greth_private *greth = netdev_priv(dev);
	int err;

	err = greth_init_rings(greth);
	if (err) {
		if (netif_msg_ifup(greth))
			dev_err(&dev->dev, "Could not allocate memory for DMA rings\n");
		return err;
	}

	err = request_irq(greth->irq, greth_interrupt, 0, "eth", (void *) dev);
	if (err) {
		if (netif_msg_ifup(greth))
			dev_err(&dev->dev, "Could not allocate interrupt %d\n", dev->irq);
		greth_clean_rings(greth);
		return err;
	}

	if (netif_msg_ifup(greth))
		dev_dbg(&dev->dev, " starting queue\n");
	netif_start_queue(dev);

	GRETH_REGSAVE(greth->regs->status, 0xFF);

	napi_enable(&greth->napi);

	greth_enable_irqs(greth);
	greth_enable_tx(greth);
	greth_enable_rx(greth);
	return 0;

}