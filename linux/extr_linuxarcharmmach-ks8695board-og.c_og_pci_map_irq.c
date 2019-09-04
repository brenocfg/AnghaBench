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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int KS8695_IRQ_EXTERN0 ; 
 int KS8695_IRQ_EXTERN1 ; 
 scalar_t__ machine_is_im4004 () ; 

__attribute__((used)) static int og_pci_map_irq(const struct pci_dev *dev, u8 slot, u8 pin)
{
	if (machine_is_im4004() && (slot == 8))
		return KS8695_IRQ_EXTERN1;
	return KS8695_IRQ_EXTERN0;
}