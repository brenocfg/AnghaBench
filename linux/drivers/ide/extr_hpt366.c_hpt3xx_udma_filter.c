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
struct hpt_info {int chip_type; } ;
struct TYPE_5__ {int ultra_mask; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_6__ {int /*<<< orphan*/  id; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int ATA_UDMA2 ; 
 int ATA_UDMA3 ; 
 int ATA_UDMA4 ; 
 int /*<<< orphan*/  HPT366_ALLOW_ATA66_3 ; 
 int /*<<< orphan*/  HPT366_ALLOW_ATA66_4 ; 
#define  HPT36x 134 
#define  HPT370 133 
#define  HPT370A 132 
 int /*<<< orphan*/  HPT370_ALLOW_ATA100_5 ; 
#define  HPT372 131 
#define  HPT372A 130 
#define  HPT372N 129 
#define  HPT374 128 
 int /*<<< orphan*/  ata_id_is_sata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bad_ata100_5 ; 
 int /*<<< orphan*/  bad_ata33 ; 
 int /*<<< orphan*/  bad_ata66_3 ; 
 int /*<<< orphan*/  bad_ata66_4 ; 
 scalar_t__ check_in_drive_list (TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct hpt_info* hpt3xx_get_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 hpt3xx_udma_filter(ide_drive_t *drive)
{
	ide_hwif_t *hwif	= drive->hwif;
	struct hpt_info *info	= hpt3xx_get_info(hwif->dev);
	u8 mask 		= hwif->ultra_mask;

	switch (info->chip_type) {
	case HPT36x:
		if (!HPT366_ALLOW_ATA66_4 ||
		    check_in_drive_list(drive, bad_ata66_4))
			mask = ATA_UDMA3;

		if (!HPT366_ALLOW_ATA66_3 ||
		    check_in_drive_list(drive, bad_ata66_3))
			mask = ATA_UDMA2;
		break;
	case HPT370:
		if (!HPT370_ALLOW_ATA100_5 ||
		    check_in_drive_list(drive, bad_ata100_5))
			mask = ATA_UDMA4;
		break;
	case HPT370A:
		if (!HPT370_ALLOW_ATA100_5 ||
		    check_in_drive_list(drive, bad_ata100_5))
			return ATA_UDMA4;
		/* fall through */
	case HPT372 :
	case HPT372A:
	case HPT372N:
	case HPT374 :
		if (ata_id_is_sata(drive->id))
			mask &= ~0x0e;
		/* fall through */
	default:
		return mask;
	}

	return check_in_drive_list(drive, bad_ata33) ? 0x00 : mask;
}