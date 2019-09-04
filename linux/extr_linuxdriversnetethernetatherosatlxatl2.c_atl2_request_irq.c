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
struct net_device {int /*<<< orphan*/  name; } ;
struct atl2_adapter {int have_msi; TYPE_1__* pdev; struct net_device* netdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int IRQF_SHARED ; 
 int /*<<< orphan*/  atl2_intr ; 
 int pci_enable_msi (TYPE_1__*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int atl2_request_irq(struct atl2_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	int flags, err = 0;

	flags = IRQF_SHARED;
	adapter->have_msi = true;
	err = pci_enable_msi(adapter->pdev);
	if (err)
		adapter->have_msi = false;

	if (adapter->have_msi)
		flags &= ~IRQF_SHARED;

	return request_irq(adapter->pdev->irq, atl2_intr, flags, netdev->name,
		netdev);
}