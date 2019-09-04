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
struct pci_dev {int revision; scalar_t__ vendor; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DEVFN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_DEVICE_ID_AL_M1533 ; 
 scalar_t__ PCI_VENDOR_ID_AL ; 
 int chip_is_1543c_e ; 
 struct pci_dev* isa_dev ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int m5229_revision ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_device (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct pci_dev* pci_get_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 

__attribute__((used)) static int init_chipset_ali15x3(struct pci_dev *dev)
{
	unsigned long flags;
	u8 tmpbyte;
	struct pci_dev *north = pci_get_slot(dev->bus, PCI_DEVFN(0,0));

	m5229_revision = dev->revision;

	isa_dev = pci_get_device(PCI_VENDOR_ID_AL, PCI_DEVICE_ID_AL_M1533, NULL);

	local_irq_save(flags);

	if (m5229_revision < 0xC2) {
		/*
		 * revision 0x20 (1543-E, 1543-F)
		 * revision 0xC0, 0xC1 (1543C-C, 1543C-D, 1543C-E)
		 * clear CD-ROM DMA write bit, m5229, 0x4b, bit 7
		 */
		pci_read_config_byte(dev, 0x4b, &tmpbyte);
		/*
		 * clear bit 7
		 */
		pci_write_config_byte(dev, 0x4b, tmpbyte & 0x7F);
		/*
		 * check m1533, 0x5e, bit 1~4 == 1001 => & 00011110 = 00010010
		 */
		if (m5229_revision >= 0x20 && isa_dev) {
			pci_read_config_byte(isa_dev, 0x5e, &tmpbyte);
			chip_is_1543c_e = ((tmpbyte & 0x1e) == 0x12) ? 1: 0;
		}
		goto out;
	}

	/*
	 * 1543C-B?, 1535, 1535D, 1553
	 * Note 1: not all "motherboard" support this detection
	 * Note 2: if no udma 66 device, the detection may "error".
	 *         but in this case, we will not set the device to
	 *         ultra 66, the detection result is not important
	 */

	/*
	 * enable "Cable Detection", m5229, 0x4b, bit3
	 */
	pci_read_config_byte(dev, 0x4b, &tmpbyte);
	pci_write_config_byte(dev, 0x4b, tmpbyte | 0x08);

	/*
	 * We should only tune the 1533 enable if we are using an ALi
	 * North bridge. We might have no north found on some zany
	 * box without a device at 0:0.0. The ALi bridge will be at
	 * 0:0.0 so if we didn't find one we know what is cooking.
	 */
	if (north && north->vendor != PCI_VENDOR_ID_AL)
		goto out;

	if (m5229_revision < 0xC5 && isa_dev)
	{	
		/*
		 * set south-bridge's enable bit, m1533, 0x79
		 */

		pci_read_config_byte(isa_dev, 0x79, &tmpbyte);
		if (m5229_revision == 0xC2) {
			/*
			 * 1543C-B0 (m1533, 0x79, bit 2)
			 */
			pci_write_config_byte(isa_dev, 0x79, tmpbyte | 0x04);
		} else if (m5229_revision >= 0xC3) {
			/*
			 * 1553/1535 (m1533, 0x79, bit 1)
			 */
			pci_write_config_byte(isa_dev, 0x79, tmpbyte | 0x02);
		}
	}

out:
	/*
	 * CD_ROM DMA on (m5229, 0x53, bit0)
	 *      Enable this bit even if we want to use PIO.
	 * PIO FIFO off (m5229, 0x53, bit1)
	 *      The hardware will use 0x54h and 0x55h to control PIO FIFO.
	 *	(Not on later devices it seems)
	 *
	 *	0x53 changes meaning on later revs - we must no touch
	 *	bit 1 on them.  Need to check if 0x20 is the right break.
	 */
	if (m5229_revision >= 0x20) {
		pci_read_config_byte(dev, 0x53, &tmpbyte);

		if (m5229_revision <= 0x20)
			tmpbyte = (tmpbyte & (~0x02)) | 0x01;
		else if (m5229_revision == 0xc7 || m5229_revision == 0xc8)
			tmpbyte |= 0x03;
		else
			tmpbyte |= 0x01;

		pci_write_config_byte(dev, 0x53, tmpbyte);
	}
	local_irq_restore(flags);
	pci_dev_put(north);
	pci_dev_put(isa_dev);
	return 0;
}