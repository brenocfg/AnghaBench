#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct pci_dev {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_7__ {int dn; int pio_mode; } ;
typedef  TYPE_2__ ide_drive_t ;
struct TYPE_8__ {int recover_width; int command_width; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATIIXP_IDE_PIO_MODE ; 
 int /*<<< orphan*/  ATIIXP_IDE_PIO_TIMING ; 
 int XFER_PIO_0 ; 
 int /*<<< orphan*/  atiixp_lock ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* pio_timing ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atiixp_set_pio_mode(ide_hwif_t *hwif, ide_drive_t *drive)
{
	struct pci_dev *dev = to_pci_dev(hwif->dev);
	unsigned long flags;
	int timing_shift = (drive->dn ^ 1) * 8;
	u32 pio_timing_data;
	u16 pio_mode_data;
	const u8 pio = drive->pio_mode - XFER_PIO_0;

	spin_lock_irqsave(&atiixp_lock, flags);

	pci_read_config_word(dev, ATIIXP_IDE_PIO_MODE, &pio_mode_data);
	pio_mode_data &= ~(0x07 << (drive->dn * 4));
	pio_mode_data |= (pio << (drive->dn * 4));
	pci_write_config_word(dev, ATIIXP_IDE_PIO_MODE, pio_mode_data);

	pci_read_config_dword(dev, ATIIXP_IDE_PIO_TIMING, &pio_timing_data);
	pio_timing_data &= ~(0xff << timing_shift);
	pio_timing_data |= (pio_timing[pio].recover_width << timing_shift) |
		 (pio_timing[pio].command_width << (timing_shift + 4));
	pci_write_config_dword(dev, ATIIXP_IDE_PIO_TIMING, pio_timing_data);

	spin_unlock_irqrestore(&atiixp_lock, flags);
}