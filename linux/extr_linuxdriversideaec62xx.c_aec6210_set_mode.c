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
typedef  int u8 ;
typedef  int u16 ;
struct pci_dev {int dummy; } ;
struct ide_host {struct chipset_bus_clock_list_entry* host_priv; } ;
struct chipset_bus_clock_list_entry {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_6__ {int dma_mode; int dn; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int pci_bus_clock_list (int const,struct chipset_bus_clock_list_entry*) ; 
 int pci_bus_clock_list_ultra (int const,struct chipset_bus_clock_list_entry*) ; 
 struct ide_host* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aec6210_set_mode(ide_hwif_t *hwif, ide_drive_t *drive)
{
	struct pci_dev *dev	= to_pci_dev(hwif->dev);
	struct ide_host *host	= pci_get_drvdata(dev);
	struct chipset_bus_clock_list_entry *bus_clock = host->host_priv;
	u16 d_conf		= 0;
	u8 ultra = 0, ultra_conf = 0;
	u8 tmp0 = 0, tmp1 = 0, tmp2 = 0;
	const u8 speed = drive->dma_mode;
	unsigned long flags;

	local_irq_save(flags);
	/* 0x40|(2*drive->dn): Active, 0x41|(2*drive->dn): Recovery */
	pci_read_config_word(dev, 0x40|(2*drive->dn), &d_conf);
	tmp0 = pci_bus_clock_list(speed, bus_clock);
	d_conf = ((tmp0 & 0xf0) << 4) | (tmp0 & 0xf);
	pci_write_config_word(dev, 0x40|(2*drive->dn), d_conf);

	tmp1 = 0x00;
	tmp2 = 0x00;
	pci_read_config_byte(dev, 0x54, &ultra);
	tmp1 = ((0x00 << (2*drive->dn)) | (ultra & ~(3 << (2*drive->dn))));
	ultra_conf = pci_bus_clock_list_ultra(speed, bus_clock);
	tmp2 = ((ultra_conf << (2*drive->dn)) | (tmp1 & ~(3 << (2*drive->dn))));
	pci_write_config_byte(dev, 0x54, tmp2);
	local_irq_restore(flags);
}