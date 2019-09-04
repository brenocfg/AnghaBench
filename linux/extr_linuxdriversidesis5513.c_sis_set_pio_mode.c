#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ide_hwif_t ;
struct TYPE_5__ {int /*<<< orphan*/  pio_mode; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  config_drive_art_rwp (TYPE_1__*) ; 
 int /*<<< orphan*/  sis_program_timings (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sis_set_pio_mode(ide_hwif_t *hwif, ide_drive_t *drive)
{
	config_drive_art_rwp(drive);
	sis_program_timings(drive, drive->pio_mode);
}