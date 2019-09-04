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
typedef  size_t u8 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int* lboxre2_irq_tab ; 
 scalar_t__ mach_is_lboxre2 () ; 
 int* rts7751r2d_irq_tab ; 

int pcibios_map_platform_irq(const struct pci_dev *pdev, u8 slot, u8 pin)
{
	if (mach_is_lboxre2())
		return lboxre2_irq_tab[slot];
	else
		return rts7751r2d_irq_tab[slot];
}