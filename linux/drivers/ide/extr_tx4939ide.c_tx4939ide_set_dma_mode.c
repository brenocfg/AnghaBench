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
struct TYPE_5__ {int select_data; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_6__ {scalar_t__ dma_mode; scalar_t__ dn; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 scalar_t__ const XFER_MW_DMA_0 ; 
 scalar_t__ const XFER_UDMA_0 ; 

__attribute__((used)) static void tx4939ide_set_dma_mode(ide_hwif_t *hwif, ide_drive_t *drive)
{
	u32 mask, val;
	const u8 mode = drive->dma_mode;

	/* Update Data Transfer Mode for this drive. */
	if (mode >= XFER_UDMA_0)
		val = mode - XFER_UDMA_0 + 8;
	else
		val = mode - XFER_MW_DMA_0 + 5;
	if (drive->dn) {
		mask = 0x00f00000;
		val <<= 20;
	} else {
		mask = 0x000000f0;
		val <<= 4;
	}
	hwif->select_data = (hwif->select_data & ~mask) | val;
	/* tx4939ide_tf_load_fixup() will set the Sys_Ctl register */
}