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
struct ata_port {struct ata_device* private_data; TYPE_1__* host; } ;
struct ata_device {int pio_mode; scalar_t__ class; int devno; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ATA_DEV_ATA ; 
 int FTIM ; 
 int /*<<< orphan*/  IDETIM ; 
 int IORDY ; 
 int PPE ; 
 int XFER_PIO_0 ; 
 scalar_t__ ata_pio_need_iordy (struct ata_device*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mpiix_set_piomode(struct ata_port *ap, struct ata_device *adev)
{
	int control = 0;
	int pio = adev->pio_mode - XFER_PIO_0;
	struct pci_dev *pdev = to_pci_dev(ap->host->dev);
	u16 idetim;
	static const	 /* ISP  RTC */
	u8 timings[][2]	= { { 0, 0 },
			    { 0, 0 },
			    { 1, 0 },
			    { 2, 1 },
			    { 2, 3 }, };

	pci_read_config_word(pdev, IDETIM, &idetim);

	/* Mask the IORDY/TIME/PPE for this device */
	if (adev->class == ATA_DEV_ATA)
		control |= PPE;		/* Enable prefetch/posting for disk */
	if (ata_pio_need_iordy(adev))
		control |= IORDY;
	if (pio > 1)
		control |= FTIM;	/* This drive is on the fast timing bank */

	/* Mask out timing and clear both TIME bank selects */
	idetim &= 0xCCEE;
	idetim &= ~(0x07  << (4 * adev->devno));
	idetim |= control << (4 * adev->devno);

	idetim |= (timings[pio][0] << 12) | (timings[pio][1] << 8);
	pci_write_config_word(pdev, IDETIM, idetim);

	/* We use ap->private_data as a pointer to the device currently
	   loaded for timing */
	ap->private_data = adev;
}