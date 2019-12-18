#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ide_hwif_t ;
struct TYPE_4__ {int /*<<< orphan*/  pio_mode; int /*<<< orphan*/  dma_mode; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  pdc202xx_set_mode (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void pdc202xx_set_pio_mode(ide_hwif_t *hwif, ide_drive_t *drive)
{
	drive->dma_mode = drive->pio_mode;
	pdc202xx_set_mode(hwif, drive);
}