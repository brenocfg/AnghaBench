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
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 

__attribute__((used)) static void pci_early_fixup_cyrix_5530(struct pci_dev *dev)
{
	u8 r;
	/* clear 'F4 Video Configuration Trap' bit */
	pci_read_config_byte(dev, 0x42, &r);
	r &= 0xfd;
	pci_write_config_byte(dev, 0x42, r);
}