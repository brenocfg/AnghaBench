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
struct pci_dev {scalar_t__ device; } ;

/* Variables and functions */
 scalar_t__ PCI_DEVICE_ID_ARTOP_ATP865 ; 
 scalar_t__ PCI_DEVICE_ID_ARTOP_ATP865R ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 

__attribute__((used)) static int init_chipset_aec62xx(struct pci_dev *dev)
{
	/* These are necessary to get AEC6280 Macintosh cards to work */
	if ((dev->device == PCI_DEVICE_ID_ARTOP_ATP865) ||
	    (dev->device == PCI_DEVICE_ID_ARTOP_ATP865R)) {
		u8 reg49h = 0, reg4ah = 0;
		/* Clear reset and test bits.  */
		pci_read_config_byte(dev, 0x49, &reg49h);
		pci_write_config_byte(dev, 0x49, reg49h & ~0x30);
		/* Enable chip interrupt output.  */
		pci_read_config_byte(dev, 0x4a, &reg4ah);
		pci_write_config_byte(dev, 0x4a, reg4ah & ~0x01);
		/* Enable burst mode. */
		pci_read_config_byte(dev, 0x4a, &reg4ah);
		pci_write_config_byte(dev, 0x4a, reg4ah | 0x80);
	}

	return 0;
}