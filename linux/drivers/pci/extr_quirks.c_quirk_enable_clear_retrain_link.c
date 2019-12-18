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
struct pci_dev {int clear_retrain_link; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*) ; 

__attribute__((used)) static void quirk_enable_clear_retrain_link(struct pci_dev *dev)
{
	dev->clear_retrain_link = 1;
	pci_info(dev, "Enable PCIe Retrain Link quirk\n");
}