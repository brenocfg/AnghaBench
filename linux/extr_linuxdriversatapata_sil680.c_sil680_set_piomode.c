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
struct ata_device {int pio_mode; int devno; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int XFER_PIO_0 ; 
 struct ata_device* ata_dev_pair (struct ata_device*) ; 
 scalar_t__ ata_pio_need_iordy (struct ata_device*) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,unsigned long,int*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,unsigned long,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,unsigned long,int) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,unsigned long,int const) ; 
 unsigned long sil680_seldev (struct ata_port*,struct ata_device*,int) ; 
 unsigned long sil680_selreg (struct ata_port*,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sil680_set_piomode(struct ata_port *ap, struct ata_device *adev)
{
	static const u16 speed_p[5] = {
		0x328A, 0x2283, 0x1104, 0x10C3, 0x10C1
	};
	static const u16 speed_t[5] = {
		0x328A, 0x2283, 0x1281, 0x10C3, 0x10C1
	};

	unsigned long tfaddr = sil680_selreg(ap, 0x02);
	unsigned long addr = sil680_seldev(ap, adev, 0x04);
	unsigned long addr_mask = 0x80 + 4 * ap->port_no;
	struct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int pio = adev->pio_mode - XFER_PIO_0;
	int lowest_pio = pio;
	int port_shift = 4 * adev->devno;
	u16 reg;
	u8 mode;

	struct ata_device *pair = ata_dev_pair(adev);

	if (pair != NULL && adev->pio_mode > pair->pio_mode)
		lowest_pio = pair->pio_mode - XFER_PIO_0;

	pci_write_config_word(pdev, addr, speed_p[pio]);
	pci_write_config_word(pdev, tfaddr, speed_t[lowest_pio]);

	pci_read_config_word(pdev, tfaddr-2, &reg);
	pci_read_config_byte(pdev, addr_mask, &mode);

	reg &= ~0x0200;			/* Clear IORDY */
	mode &= ~(3 << port_shift);	/* Clear IORDY and DMA bits */

	if (ata_pio_need_iordy(adev)) {
		reg |= 0x0200;		/* Enable IORDY */
		mode |= 1 << port_shift;
	}
	pci_write_config_word(pdev, tfaddr-2, reg);
	pci_write_config_byte(pdev, addr_mask, mode);
}