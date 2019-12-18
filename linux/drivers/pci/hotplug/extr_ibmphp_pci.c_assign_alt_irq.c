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
typedef  int u8 ;
struct pci_func {int* irq; } ;

/* Variables and functions */
 int LAN_IRQ ; 
 int OTHER_IRQ ; 
#define  PCI_BASE_CLASS_NETWORK 129 
#define  PCI_BASE_CLASS_STORAGE 128 
 int SCSI_IRQ ; 

__attribute__((used)) static void assign_alt_irq(struct pci_func *cur_func, u8 class_code)
{
	int j;
	for (j = 0; j < 4; j++) {
		if (cur_func->irq[j] == 0xff) {
			switch (class_code) {
				case PCI_BASE_CLASS_STORAGE:
					cur_func->irq[j] = SCSI_IRQ;
					break;
				case PCI_BASE_CLASS_NETWORK:
					cur_func->irq[j] = LAN_IRQ;
					break;
				default:
					cur_func->irq[j] = OTHER_IRQ;
					break;
			}
		}
	}
}