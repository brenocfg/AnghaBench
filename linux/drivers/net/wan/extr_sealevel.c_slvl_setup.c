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
struct slvl_device {TYPE_1__* chan; } ;
struct net_device {int base_addr; int irq; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  xmit; int /*<<< orphan*/  attach; } ;
struct TYPE_3__ {struct net_device* netdevice; } ;

/* Variables and functions */
 struct net_device* alloc_hdlcdev (struct slvl_device*) ; 
 TYPE_2__* dev_to_hdlc (struct net_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ register_hdlc_device (struct net_device*) ; 
 int /*<<< orphan*/  sealevel_attach ; 
 int /*<<< orphan*/  sealevel_ops ; 
 int /*<<< orphan*/  sealevel_queue_xmit ; 

__attribute__((used)) static int slvl_setup(struct slvl_device *sv, int iobase, int irq)
{
	struct net_device *dev = alloc_hdlcdev(sv);
	if (!dev)
		return -1;

	dev_to_hdlc(dev)->attach = sealevel_attach;
	dev_to_hdlc(dev)->xmit = sealevel_queue_xmit;
	dev->netdev_ops = &sealevel_ops;
	dev->base_addr = iobase;
	dev->irq = irq;

	if (register_hdlc_device(dev)) {
		pr_err("unable to register HDLC device\n");
		free_netdev(dev);
		return -1;
	}

	sv->chan->netdevice = dev;
	return 0;
}