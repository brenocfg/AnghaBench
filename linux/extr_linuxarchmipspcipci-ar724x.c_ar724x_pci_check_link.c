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
typedef  int u32 ;
struct ar724x_pci_controller {scalar_t__ ctrl_base; } ;

/* Variables and functions */
 scalar_t__ AR724X_PCI_REG_RESET ; 
 int AR724X_PCI_RESET_LINK_UP ; 
 int __raw_readl (scalar_t__) ; 

__attribute__((used)) static inline bool ar724x_pci_check_link(struct ar724x_pci_controller *apc)
{
	u32 reset;

	reset = __raw_readl(apc->ctrl_base + AR724X_PCI_REG_RESET);
	return reset & AR724X_PCI_RESET_LINK_UP;
}