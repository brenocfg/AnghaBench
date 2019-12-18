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
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {TYPE_1__* bus; } ;
struct hl_device {struct pci_dev* pdev; } ;
struct TYPE_2__ {struct pci_dev* self; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_BRIDGE_CONTROL ; 
 int /*<<< orphan*/  PCI_BRIDGE_CTL_BUS_RESET ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssleep (int) ; 

__attribute__((used)) static void hl_pci_reset_link_through_bridge(struct hl_device *hdev)
{
	struct pci_dev *pdev = hdev->pdev;
	struct pci_dev *parent_port;
	u16 val;

	parent_port = pdev->bus->self;
	pci_read_config_word(parent_port, PCI_BRIDGE_CONTROL, &val);
	val |= PCI_BRIDGE_CTL_BUS_RESET;
	pci_write_config_word(parent_port, PCI_BRIDGE_CONTROL, val);
	ssleep(1);

	val &= ~(PCI_BRIDGE_CTL_BUS_RESET);
	pci_write_config_word(parent_port, PCI_BRIDGE_CONTROL, val);
	ssleep(3);
}