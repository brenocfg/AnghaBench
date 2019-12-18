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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_BASE_CLASS_DISPLAY ; 
 int /*<<< orphan*/  pci_create_device_link (struct pci_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void quirk_gpu_usb(struct pci_dev *usb)
{
	pci_create_device_link(usb, 2, 0, PCI_BASE_CLASS_DISPLAY, 16);
}