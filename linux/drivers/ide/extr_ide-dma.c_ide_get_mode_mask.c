#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct ide_port_ops {unsigned int (* udma_filter ) (TYPE_2__*) ;unsigned int (* mdma_filter ) (TYPE_2__*) ;} ;
struct TYPE_7__ {unsigned int ultra_mask; unsigned int mwdma_mask; unsigned int swdma_mask; struct ide_port_ops* port_ops; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_8__ {int* id; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 size_t ATA_ID_CFA_MODES ; 
 size_t ATA_ID_FIELD_VALID ; 
 size_t ATA_ID_MWDMA_MODES ; 
 size_t ATA_ID_OLD_DMA_MODES ; 
 size_t ATA_ID_SWDMA_MODES ; 
 size_t ATA_ID_UDMA_MODES ; 
 unsigned int ATA_SWDMA2 ; 
 int /*<<< orphan*/  BUG () ; 
#define  XFER_MW_DMA_0 130 
#define  XFER_SW_DMA_0 129 
#define  XFER_UDMA_0 128 
 int XFER_UDMA_2 ; 
 int /*<<< orphan*/  ata_id_is_cfa (int*) ; 
 int /*<<< orphan*/  eighty_ninty_three (TYPE_2__*) ; 
 unsigned int stub1 (TYPE_2__*) ; 
 unsigned int stub2 (TYPE_2__*) ; 

__attribute__((used)) static unsigned int ide_get_mode_mask(ide_drive_t *drive, u8 base, u8 req_mode)
{
	u16 *id = drive->id;
	ide_hwif_t *hwif = drive->hwif;
	const struct ide_port_ops *port_ops = hwif->port_ops;
	unsigned int mask = 0;

	switch (base) {
	case XFER_UDMA_0:
		if ((id[ATA_ID_FIELD_VALID] & 4) == 0)
			break;
		mask = id[ATA_ID_UDMA_MODES];
		if (port_ops && port_ops->udma_filter)
			mask &= port_ops->udma_filter(drive);
		else
			mask &= hwif->ultra_mask;

		/*
		 * avoid false cable warning from eighty_ninty_three()
		 */
		if (req_mode > XFER_UDMA_2) {
			if ((mask & 0x78) && (eighty_ninty_three(drive) == 0))
				mask &= 0x07;
		}
		break;
	case XFER_MW_DMA_0:
		mask = id[ATA_ID_MWDMA_MODES];

		/* Also look for the CF specific MWDMA modes... */
		if (ata_id_is_cfa(id) && (id[ATA_ID_CFA_MODES] & 0x38)) {
			u8 mode = ((id[ATA_ID_CFA_MODES] & 0x38) >> 3) - 1;

			mask |= ((2 << mode) - 1) << 3;
		}

		if (port_ops && port_ops->mdma_filter)
			mask &= port_ops->mdma_filter(drive);
		else
			mask &= hwif->mwdma_mask;
		break;
	case XFER_SW_DMA_0:
		mask = id[ATA_ID_SWDMA_MODES];
		if (!(mask & ATA_SWDMA2) && (id[ATA_ID_OLD_DMA_MODES] >> 8)) {
			u8 mode = id[ATA_ID_OLD_DMA_MODES] >> 8;

			/*
			 * if the mode is valid convert it to the mask
			 * (the maximum allowed mode is XFER_SW_DMA_2)
			 */
			if (mode <= 2)
				mask = (2 << mode) - 1;
		}
		mask &= hwif->swdma_mask;
		break;
	default:
		BUG();
		break;
	}

	return mask;
}