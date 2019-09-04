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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct pci_dev {int dummy; } ;
struct ata_port {int port_no; TYPE_1__* host; } ;
struct ata_device {scalar_t__ dma_mode; int devno; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ XFER_MW_DMA_0 ; 
 unsigned int const XFER_PIO_0 ; 
 unsigned int const XFER_PIO_3 ; 
 unsigned int const XFER_PIO_4 ; 
 scalar_t__ XFER_UDMA_0 ; 
 int min (int,unsigned int) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,scalar_t__*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,scalar_t__) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int,int) ; 
 int /*<<< orphan*/  piix_lock ; 
 int /*<<< orphan*/  piix_set_timings (struct ata_port*,struct ata_device*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_pata_set_dmamode(struct ata_port *ap, struct ata_device *adev, int isich)
{
	struct pci_dev *dev	= to_pci_dev(ap->host->dev);
	unsigned long flags;
	u8 speed		= adev->dma_mode;
	int devid		= adev->devno + 2 * ap->port_no;
	u8 udma_enable		= 0;

	if (speed >= XFER_UDMA_0) {
		unsigned int udma = speed - XFER_UDMA_0;
		u16 udma_timing;
		u16 ideconf;
		int u_clock, u_speed;

		spin_lock_irqsave(&piix_lock, flags);

		pci_read_config_byte(dev, 0x48, &udma_enable);

		/*
		 * UDMA is handled by a combination of clock switching and
		 * selection of dividers
		 *
		 * Handy rule: Odd modes are UDMATIMx 01, even are 02
		 *	       except UDMA0 which is 00
		 */
		u_speed = min(2 - (udma & 1), udma);
		if (udma == 5)
			u_clock = 0x1000;	/* 100Mhz */
		else if (udma > 2)
			u_clock = 1;		/* 66Mhz */
		else
			u_clock = 0;		/* 33Mhz */

		udma_enable |= (1 << devid);

		/* Load the CT/RP selection */
		pci_read_config_word(dev, 0x4A, &udma_timing);
		udma_timing &= ~(3 << (4 * devid));
		udma_timing |= u_speed << (4 * devid);
		pci_write_config_word(dev, 0x4A, udma_timing);

		if (isich) {
			/* Select a 33/66/100Mhz clock */
			pci_read_config_word(dev, 0x54, &ideconf);
			ideconf &= ~(0x1001 << devid);
			ideconf |= u_clock << devid;
			/* For ICH or later we should set bit 10 for better
			   performance (WR_PingPong_En) */
			pci_write_config_word(dev, 0x54, ideconf);
		}

		pci_write_config_byte(dev, 0x48, udma_enable);

		spin_unlock_irqrestore(&piix_lock, flags);
	} else {
		/* MWDMA is driven by the PIO timings. */
		unsigned int mwdma = speed - XFER_MW_DMA_0;
		const unsigned int needed_pio[3] = {
			XFER_PIO_0, XFER_PIO_3, XFER_PIO_4
		};
		int pio = needed_pio[mwdma] - XFER_PIO_0;

		/* XFER_PIO_0 is never used currently */
		piix_set_timings(ap, adev, pio);
	}
}