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
struct set_msi_sid_data {int count; int busmatch_count; int /*<<< orphan*/  alias; TYPE_2__* pdev; } ;
struct pci_dev {TYPE_3__* bus; } ;
struct irte {int dummy; } ;
struct TYPE_6__ {scalar_t__ number; } ;
struct TYPE_5__ {TYPE_1__* bus; } ;
struct TYPE_4__ {scalar_t__ number; } ;

/* Variables and functions */
 scalar_t__ PCI_BUS_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SQ_ALL_16 ; 
 int /*<<< orphan*/  SVT_VERIFY_SID_SQ ; 
 int /*<<< orphan*/  pci_dev_id (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_for_each_dma_alias (struct pci_dev*,int /*<<< orphan*/ ,struct set_msi_sid_data*) ; 
 int /*<<< orphan*/  set_irte_sid (struct irte*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_irte_verify_bus (struct irte*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  set_msi_sid_cb ; 

__attribute__((used)) static int set_msi_sid(struct irte *irte, struct pci_dev *dev)
{
	struct set_msi_sid_data data;

	if (!irte || !dev)
		return -1;

	data.count = 0;
	data.busmatch_count = 0;
	pci_for_each_dma_alias(dev, set_msi_sid_cb, &data);

	/*
	 * DMA alias provides us with a PCI device and alias.  The only case
	 * where the it will return an alias on a different bus than the
	 * device is the case of a PCIe-to-PCI bridge, where the alias is for
	 * the subordinate bus.  In this case we can only verify the bus.
	 *
	 * If there are multiple aliases, all with the same bus number,
	 * then all we can do is verify the bus. This is typical in NTB
	 * hardware which use proxy IDs where the device will generate traffic
	 * from multiple devfn numbers on the same bus.
	 *
	 * If the alias device is on a different bus than our source device
	 * then we have a topology based alias, use it.
	 *
	 * Otherwise, the alias is for a device DMA quirk and we cannot
	 * assume that MSI uses the same requester ID.  Therefore use the
	 * original device.
	 */
	if (PCI_BUS_NUM(data.alias) != data.pdev->bus->number)
		set_irte_verify_bus(irte, PCI_BUS_NUM(data.alias),
				    dev->bus->number);
	else if (data.count >= 2 && data.busmatch_count == data.count)
		set_irte_verify_bus(irte, dev->bus->number, dev->bus->number);
	else if (data.pdev->bus->number != dev->bus->number)
		set_irte_sid(irte, SVT_VERIFY_SID_SQ, SQ_ALL_16, data.alias);
	else
		set_irte_sid(irte, SVT_VERIFY_SID_SQ, SQ_ALL_16,
			     pci_dev_id(dev));

	return 0;
}