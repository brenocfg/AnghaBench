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
struct TYPE_6__ {int rqsize; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_7__ {TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  is_dev_seagate_sata (TYPE_2__*) ; 
 int /*<<< orphan*/  is_sata (TYPE_1__*) ; 

__attribute__((used)) static void sil_quirkproc(ide_drive_t *drive)
{
	ide_hwif_t *hwif = drive->hwif;

	/* Try and rise the rqsize */
	if (!is_sata(hwif) || !is_dev_seagate_sata(drive))
		hwif->rqsize = 128;
}