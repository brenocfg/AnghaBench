#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * timings; } ;
typedef  TYPE_2__ pmac_ide_hwif_t ;
struct TYPE_7__ {int /*<<< orphan*/  parent; } ;
struct TYPE_9__ {TYPE_1__ gendev; } ;
typedef  TYPE_3__ ide_hwif_t ;
struct TYPE_10__ {int dn; TYPE_3__* hwif; } ;
typedef  TYPE_4__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  IDE_KAUAI_PIO_CONFIG ; 
 int /*<<< orphan*/  IDE_KAUAI_ULTRA_CONFIG ; 
 int /*<<< orphan*/  PMAC_IDE_REG (int /*<<< orphan*/ ) ; 
 TYPE_2__* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pmac_ide_kauai_apply_timings(ide_drive_t *drive)
{
	ide_hwif_t *hwif = drive->hwif;
	pmac_ide_hwif_t *pmif = dev_get_drvdata(hwif->gendev.parent);

	if (drive->dn & 1) {
		writel(pmif->timings[1], PMAC_IDE_REG(IDE_KAUAI_PIO_CONFIG));
		writel(pmif->timings[3], PMAC_IDE_REG(IDE_KAUAI_ULTRA_CONFIG));
	} else {
		writel(pmif->timings[0], PMAC_IDE_REG(IDE_KAUAI_PIO_CONFIG));
		writel(pmif->timings[2], PMAC_IDE_REG(IDE_KAUAI_ULTRA_CONFIG));
	}
	(void)readl(PMAC_IDE_REG(IDE_KAUAI_PIO_CONFIG));
}