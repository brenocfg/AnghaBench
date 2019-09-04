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
struct net_device {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ei_close (struct net_device*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int ne2k_pci_close(struct net_device *dev)
{
	ei_close(dev);
	free_irq(dev->irq, dev);
	return 0;
}