#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct TYPE_6__ {TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ATA_100 ; 
 scalar_t__ ATA_133 ; 
 scalar_t__ const XFER_MW_DMA_0 ; 
 scalar_t__ const XFER_PIO_0 ; 
 int** act_time_value ; 
 int** ini_time_value ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,scalar_t__,int) ; 
 int** rco_time_value ; 
 scalar_t__ sis_ata133_get_base (TYPE_2__*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sis_ata133_program_timings(ide_drive_t *drive, const u8 mode)
{
	struct pci_dev *dev = to_pci_dev(drive->hwif->dev);
	u32 t1 = 0;
	u8 drive_pci = sis_ata133_get_base(drive), clk, idx;

	pci_read_config_dword(dev, drive_pci, &t1);

	t1 &= 0xc0c00fff;
	clk = (t1 & 0x08) ? ATA_133 : ATA_100;
	if (mode >= XFER_MW_DMA_0) {
		t1 &= ~0x04;	/* disable UDMA */
		idx = mode - XFER_MW_DMA_0 + 5;
	} else
		idx = mode - XFER_PIO_0;
	t1 |= ini_time_value[clk][idx] << 12;
	t1 |= act_time_value[clk][idx] << 16;
	t1 |= rco_time_value[clk][idx] << 24;

	pci_write_config_dword(dev, drive_pci, t1);
}