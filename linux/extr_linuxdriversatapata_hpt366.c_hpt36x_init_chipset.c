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
 int L1_CACHE_BYTES ; 
 int PCI_CACHE_LINE_SIZE ; 
 int PCI_LATENCY_TIMER ; 
 int PCI_MAX_LAT ; 
 int PCI_MIN_GNT ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 

__attribute__((used)) static void hpt36x_init_chipset(struct pci_dev *dev)
{
	u8 drive_fast;

	pci_write_config_byte(dev, PCI_CACHE_LINE_SIZE, (L1_CACHE_BYTES / 4));
	pci_write_config_byte(dev, PCI_LATENCY_TIMER, 0x78);
	pci_write_config_byte(dev, PCI_MIN_GNT, 0x08);
	pci_write_config_byte(dev, PCI_MAX_LAT, 0x08);

	pci_read_config_byte(dev, 0x51, &drive_fast);
	if (drive_fast & 0x80)
		pci_write_config_byte(dev, 0x51, drive_fast & ~0x80);
}