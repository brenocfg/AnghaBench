#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct pci_dev {int dummy; } ;
struct ata_timing {int /*<<< orphan*/  recover; int /*<<< orphan*/  active; } ;
struct ata_port {int port_no; TYPE_1__* host; } ;
struct ata_device {int devno; int /*<<< orphan*/  pio_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int XFER_MW_DMA_0 ; 
 int /*<<< orphan*/  ata_pio_need_iordy (struct ata_device*) ; 
 int /*<<< orphan*/  ata_timing_compute (struct ata_device*,int /*<<< orphan*/ ,struct ata_timing*,unsigned long,int /*<<< orphan*/ ) ; 
 int clamp_val (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ns87415_set_mode(struct ata_port *ap, struct ata_device *adev, u8 mode)
{
	struct pci_dev *dev	= to_pci_dev(ap->host->dev);
	int unit		= 2 * ap->port_no + adev->devno;
	int timing		= 0x44 + 2 * unit;
	unsigned long T		= 1000000000 / 33333;	/* PCI clocks */
	struct ata_timing t;
	u16 clocking;
	u8 iordy;
	u8 status;

	/* Timing register format is 17 - low nybble read timing with
	   the high nybble being 16 - x for recovery time in PCI clocks */

	ata_timing_compute(adev, adev->pio_mode, &t, T, 0);

	clocking = 17 - clamp_val(t.active, 2, 17);
	clocking |= (16 - clamp_val(t.recover, 1, 16)) << 4;
 	/* Use the same timing for read and write bytes */
	clocking |= (clocking << 8);
	pci_write_config_word(dev, timing, clocking);

	/* Set the IORDY enable versus DMA enable on or off properly */
	pci_read_config_byte(dev, 0x42, &iordy);
	iordy &= ~(1 << (4 + unit));
	if (mode >= XFER_MW_DMA_0 || !ata_pio_need_iordy(adev))
		iordy |= (1 << (4 + unit));

	/* Paranoia: We shouldn't ever get here with busy write buffers
	   but if so wait */

	pci_read_config_byte(dev, 0x43, &status);
	while (status & 0x03) {
		udelay(1);
		pci_read_config_byte(dev, 0x43, &status);
	}
	/* Flip the IORDY/DMA bits now we are sure the write buffers are
	   clear */
	pci_write_config_byte(dev, 0x42, iordy);

	/* TODO: Set byte 54 command timing to the best 8bit
	   mode shared by all four devices */
}