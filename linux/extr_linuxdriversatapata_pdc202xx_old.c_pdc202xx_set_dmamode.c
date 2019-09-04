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
struct pci_dev {int dummy; } ;
struct ata_port {int port_no; TYPE_1__* host; } ;
struct ata_device {int devno; scalar_t__ dma_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int XFER_MW_DMA_0 ; 
 scalar_t__ XFER_UDMA_0 ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pdc202xx_set_dmamode(struct ata_port *ap, struct ata_device *adev)
{
	struct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int port = 0x60 + 8 * ap->port_no + 4 * adev->devno;
	static u8 udma_timing[6][2] = {
		{ 0x60, 0x03 },	/* 33 Mhz Clock */
		{ 0x40, 0x02 },
		{ 0x20, 0x01 },
		{ 0x40, 0x02 },	/* 66 Mhz Clock */
		{ 0x20, 0x01 },
		{ 0x20, 0x01 }
	};
	static u8 mdma_timing[3][2] = {
		{ 0xe0, 0x0f },
		{ 0x60, 0x04 },
		{ 0x60, 0x03 },
	};
	u8 r_bp, r_cp;

	pci_read_config_byte(pdev, port + 1, &r_bp);
	pci_read_config_byte(pdev, port + 2, &r_cp);

	r_bp &= ~0xE0;
	r_cp &= ~0x0F;

	if (adev->dma_mode >= XFER_UDMA_0) {
		int speed = adev->dma_mode - XFER_UDMA_0;
		r_bp |= udma_timing[speed][0];
		r_cp |= udma_timing[speed][1];

	} else {
		int speed = adev->dma_mode - XFER_MW_DMA_0;
		r_bp |= mdma_timing[speed][0];
		r_cp |= mdma_timing[speed][1];
	}
	pci_write_config_byte(pdev, port + 1, r_bp);
	pci_write_config_byte(pdev, port + 2, r_cp);

}