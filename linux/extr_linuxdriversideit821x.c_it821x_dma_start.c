#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct it821x_dev {scalar_t__* mwdma; scalar_t__* udma; scalar_t__ timing10; } ;
typedef  int /*<<< orphan*/  ide_hwif_t ;
struct TYPE_6__ {int dn; int /*<<< orphan*/ * hwif; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 scalar_t__ MWDMA_OFF ; 
 scalar_t__ UDMA_OFF ; 
 int /*<<< orphan*/  ide_dma_start (TYPE_1__*) ; 
 struct it821x_dev* ide_get_hwifdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  it821x_program (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  it821x_program_udma (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void it821x_dma_start(ide_drive_t *drive)
{
	ide_hwif_t *hwif = drive->hwif;
	struct it821x_dev *itdev = ide_get_hwifdata(hwif);
	u8 unit = drive->dn & 1;

	if(itdev->mwdma[unit] != MWDMA_OFF)
		it821x_program(drive, itdev->mwdma[unit]);
	else if(itdev->udma[unit] != UDMA_OFF && itdev->timing10)
		it821x_program_udma(drive, itdev->udma[unit]);
	ide_dma_start(drive);
}