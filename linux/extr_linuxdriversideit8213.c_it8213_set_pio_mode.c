#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct pci_dev {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_7__ {int dn; int pio_mode; scalar_t__ media; } ;
typedef  TYPE_2__ ide_drive_t ;
typedef  int /*<<< orphan*/  DEFINE_SPINLOCK ;

/* Variables and functions */
 int XFER_PIO_0 ; 
 scalar_t__ ide_disk ; 
 scalar_t__ ide_pio_need_iordy (TYPE_2__*,int const) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void it8213_set_pio_mode(ide_hwif_t *hwif, ide_drive_t *drive)
{
	struct pci_dev *dev	= to_pci_dev(hwif->dev);
	int is_slave		= drive->dn & 1;
	int master_port		= 0x40;
	int slave_port		= 0x44;
	unsigned long flags;
	u16 master_data;
	u8 slave_data;
	static DEFINE_SPINLOCK(tune_lock);
	int control = 0;
	const u8 pio = drive->pio_mode - XFER_PIO_0;

	static const u8 timings[][2] = {
					{ 0, 0 },
					{ 0, 0 },
					{ 1, 0 },
					{ 2, 1 },
					{ 2, 3 }, };

	spin_lock_irqsave(&tune_lock, flags);
	pci_read_config_word(dev, master_port, &master_data);

	if (pio > 1)
		control |= 1;	/* Programmable timing on */
	if (drive->media != ide_disk)
		control |= 4;	/* ATAPI */
	if (ide_pio_need_iordy(drive, pio))
		control |= 2;	/* IORDY */
	if (is_slave) {
		master_data |=  0x4000;
		master_data &= ~0x0070;
		if (pio > 1)
			master_data = master_data | (control << 4);
		pci_read_config_byte(dev, slave_port, &slave_data);
		slave_data = slave_data & 0xf0;
		slave_data = slave_data | (timings[pio][0] << 2) | timings[pio][1];
	} else {
		master_data &= ~0x3307;
		if (pio > 1)
			master_data = master_data | control;
		master_data = master_data | (timings[pio][0] << 12) | (timings[pio][1] << 8);
	}
	pci_write_config_word(dev, master_port, master_data);
	if (is_slave)
		pci_write_config_byte(dev, slave_port, slave_data);
	spin_unlock_irqrestore(&tune_lock, flags);
}