#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct pci_dev {int dummy; } ;
struct TYPE_3__ {scalar_t__ channel; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;

/* Variables and functions */
 int inb (unsigned long) ; 
 unsigned long pci_resource_start (struct pci_dev*,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pdc202xx_test_irq(ide_hwif_t *hwif)
{
	struct pci_dev *dev	= to_pci_dev(hwif->dev);
	unsigned long high_16	= pci_resource_start(dev, 4);
	u8 sc1d			= inb(high_16 + 0x1d);

	if (hwif->channel) {
		/*
		 * bit 7: error, bit 6: interrupting,
		 * bit 5: FIFO full, bit 4: FIFO empty
		 */
		return (sc1d & 0x40) ? 1 : 0;
	} else	{
		/*
		 * bit 3: error, bit 2: interrupting,
		 * bit 1: FIFO full, bit 0: FIFO empty
		 */
		return (sc1d & 0x04) ? 1 : 0;
	}
}