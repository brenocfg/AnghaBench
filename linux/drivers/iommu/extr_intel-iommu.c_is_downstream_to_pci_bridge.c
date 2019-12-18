#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {TYPE_3__* bus; TYPE_2__* subordinate; } ;
struct device {int dummy; } ;
struct TYPE_6__ {scalar_t__ number; } ;
struct TYPE_4__ {scalar_t__ end; } ;
struct TYPE_5__ {scalar_t__ number; TYPE_1__ busn_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_is_pci (struct device*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static bool
is_downstream_to_pci_bridge(struct device *dev, struct device *bridge)
{
	struct pci_dev *pdev, *pbridge;

	if (!dev_is_pci(dev) || !dev_is_pci(bridge))
		return false;

	pdev = to_pci_dev(dev);
	pbridge = to_pci_dev(bridge);

	if (pbridge->subordinate &&
	    pbridge->subordinate->number <= pdev->bus->number &&
	    pbridge->subordinate->busn_res.end >= pdev->bus->number)
		return true;

	return false;
}