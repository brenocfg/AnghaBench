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
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {int ne2k_flags; } ;

/* Variables and functions */
 int FORCE_FDX ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  ei_interrupt ; 
 int /*<<< orphan*/  ei_open (struct net_device*) ; 
 TYPE_1__ ei_status ; 
 int /*<<< orphan*/  ne2k_pci_set_fdx (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int ne2k_pci_open(struct net_device *dev)
{
	int ret = request_irq(dev->irq, ei_interrupt, IRQF_SHARED, dev->name, dev);
	if (ret)
		return ret;

	if (ei_status.ne2k_flags & FORCE_FDX)
		ne2k_pci_set_fdx(dev);

	ei_open(dev);
	return 0;
}