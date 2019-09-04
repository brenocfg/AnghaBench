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
struct hpt_timings {int pio_mask; int dma_mask; int ultra_mask; } ;
struct hpt_info {struct hpt_timings* timings; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_6__ {int dn; scalar_t__ dma_mode; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 scalar_t__ const XFER_MW_DMA_0 ; 
 scalar_t__ const XFER_UDMA_0 ; 
 int get_speed_setting (scalar_t__ const,struct hpt_info*) ; 
 struct hpt_info* hpt3xx_get_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,scalar_t__,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hpt3xx_set_mode(ide_hwif_t *hwif, ide_drive_t *drive)
{
	struct pci_dev *dev	= to_pci_dev(hwif->dev);
	struct hpt_info *info	= hpt3xx_get_info(hwif->dev);
	struct hpt_timings *t	= info->timings;
	u8  itr_addr		= 0x40 + (drive->dn * 4);
	u32 old_itr		= 0;
	const u8 speed		= drive->dma_mode;
	u32 new_itr		= get_speed_setting(speed, info);
	u32 itr_mask		= speed < XFER_MW_DMA_0 ? t->pio_mask :
				 (speed < XFER_UDMA_0   ? t->dma_mask :
							  t->ultra_mask);

	pci_read_config_dword(dev, itr_addr, &old_itr);
	new_itr = (old_itr & ~itr_mask) | (new_itr & itr_mask);
	/*
	 * Disable on-chip PIO FIFO/buffer (and PIO MST mode as well)
	 * to avoid problems handling I/O errors later
	 */
	new_itr &= ~0xc0000000;

	pci_write_config_dword(dev, itr_addr, new_itr);
}