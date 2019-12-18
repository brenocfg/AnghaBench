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
 int /*<<< orphan*/  MRDMODE ; 
 int /*<<< orphan*/  PCI_LATENCY_TIMER ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int init_chipset_cmd64x(struct pci_dev *dev)
{
	u8 mrdmode = 0;

	/* Set a good latency timer and cache line size value. */
	(void) pci_write_config_byte(dev, PCI_LATENCY_TIMER, 64);
	/* FIXME: pci_set_master() to ensure a good latency timer value */

	/*
	 * Enable interrupts, select MEMORY READ LINE for reads.
	 *
	 * NOTE: although not mentioned in the PCI0646U specs,
	 * bits 0-1 are write only and won't be read back as
	 * set or not -- PCI0646U2 specs clarify this point.
	 */
	(void) pci_read_config_byte (dev, MRDMODE, &mrdmode);
	mrdmode &= ~0x30;
	(void) pci_write_config_byte(dev, MRDMODE, (mrdmode | 0x02));

	return 0;
}