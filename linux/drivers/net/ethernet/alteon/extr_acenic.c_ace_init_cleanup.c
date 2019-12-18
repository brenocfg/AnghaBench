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
struct net_device {scalar_t__ irq; } ;
struct ace_private {int /*<<< orphan*/  regs; int /*<<< orphan*/  trace_buf; int /*<<< orphan*/  skb; int /*<<< orphan*/  info_dma; scalar_t__ info; int /*<<< orphan*/  pdev; } ;
struct ace_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ace_free_descriptors (struct net_device*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct net_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct ace_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ace_init_cleanup(struct net_device *dev)
{
	struct ace_private *ap;

	ap = netdev_priv(dev);

	ace_free_descriptors(dev);

	if (ap->info)
		pci_free_consistent(ap->pdev, sizeof(struct ace_info),
				    ap->info, ap->info_dma);
	kfree(ap->skb);
	kfree(ap->trace_buf);

	if (dev->irq)
		free_irq(dev->irq, dev);

	iounmap(ap->regs);
}