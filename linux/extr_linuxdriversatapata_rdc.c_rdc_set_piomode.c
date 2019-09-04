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
struct ata_port {int port_no; TYPE_1__* host; } ;
struct ata_device {unsigned int pio_mode; int devno; scalar_t__ class; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ATA_DEV_ATA ; 
 unsigned int XFER_PIO_0 ; 
 scalar_t__ ata_pio_need_iordy (struct ata_device*) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,unsigned int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,unsigned int,int) ; 
 int /*<<< orphan*/  rdc_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rdc_set_piomode(struct ata_port *ap, struct ata_device *adev)
{
	unsigned int pio	= adev->pio_mode - XFER_PIO_0;
	struct pci_dev *dev	= to_pci_dev(ap->host->dev);
	unsigned long flags;
	unsigned int is_slave	= (adev->devno != 0);
	unsigned int master_port= ap->port_no ? 0x42 : 0x40;
	unsigned int slave_port	= 0x44;
	u16 master_data;
	u8 slave_data;
	u8 udma_enable;
	int control = 0;

	static const	 /* ISP  RTC */
	u8 timings[][2]	= { { 0, 0 },
			    { 0, 0 },
			    { 1, 0 },
			    { 2, 1 },
			    { 2, 3 }, };

	if (pio >= 2)
		control |= 1;	/* TIME1 enable */
	if (ata_pio_need_iordy(adev))
		control |= 2;	/* IE enable */

	if (adev->class == ATA_DEV_ATA)
		control |= 4;	/* PPE enable */

	spin_lock_irqsave(&rdc_lock, flags);

	/* PIO configuration clears DTE unconditionally.  It will be
	 * programmed in set_dmamode which is guaranteed to be called
	 * after set_piomode if any DMA mode is available.
	 */
	pci_read_config_word(dev, master_port, &master_data);
	if (is_slave) {
		/* clear TIME1|IE1|PPE1|DTE1 */
		master_data &= 0xff0f;
		/* Enable SITRE (separate slave timing register) */
		master_data |= 0x4000;
		/* enable PPE1, IE1 and TIME1 as needed */
		master_data |= (control << 4);
		pci_read_config_byte(dev, slave_port, &slave_data);
		slave_data &= (ap->port_no ? 0x0f : 0xf0);
		/* Load the timing nibble for this slave */
		slave_data |= ((timings[pio][0] << 2) | timings[pio][1])
						<< (ap->port_no ? 4 : 0);
	} else {
		/* clear ISP|RCT|TIME0|IE0|PPE0|DTE0 */
		master_data &= 0xccf0;
		/* Enable PPE, IE and TIME as appropriate */
		master_data |= control;
		/* load ISP and RCT */
		master_data |=
			(timings[pio][0] << 12) |
			(timings[pio][1] << 8);
	}
	pci_write_config_word(dev, master_port, master_data);
	if (is_slave)
		pci_write_config_byte(dev, slave_port, slave_data);

	/* Ensure the UDMA bit is off - it will be turned back on if
	   UDMA is selected */

	pci_read_config_byte(dev, 0x48, &udma_enable);
	udma_enable &= ~(1 << (2 * ap->port_no + adev->devno));
	pci_write_config_byte(dev, 0x48, udma_enable);

	spin_unlock_irqrestore(&rdc_lock, flags);
}