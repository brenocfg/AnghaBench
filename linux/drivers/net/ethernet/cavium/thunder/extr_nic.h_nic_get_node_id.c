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
typedef  int u64 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int NIC_NODE_ID_MASK ; 
 int NIC_NODE_ID_SHIFT ; 
 int /*<<< orphan*/  PCI_CFG_REG_BAR_NUM ; 
 int pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int nic_get_node_id(struct pci_dev *pdev)
{
	u64 addr = pci_resource_start(pdev, PCI_CFG_REG_BAR_NUM);
	return ((addr >> NIC_NODE_ID_SHIFT) & NIC_NODE_ID_MASK);
}