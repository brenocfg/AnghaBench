#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_7__ {TYPE_1__* tp_ops; } ;
typedef  TYPE_2__ ide_hwif_t ;
struct TYPE_8__ {int /*<<< orphan*/  name; TYPE_2__* hwif; } ;
typedef  TYPE_3__ ide_drive_t ;
struct TYPE_6__ {int (* read_status ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int ATA_BUSY ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static u8 wait_drive_not_busy(ide_drive_t *drive)
{
	ide_hwif_t *hwif = drive->hwif;
	int retries;
	u8 stat;

	/*
	 * Last sector was transferred, wait until device is ready.  This can
	 * take up to 6 ms on some ATAPI devices, so we will wait max 10 ms.
	 */
	for (retries = 0; retries < 1000; retries++) {
		stat = hwif->tp_ops->read_status(hwif);

		if (stat & ATA_BUSY)
			udelay(10);
		else
			break;
	}

	if (stat & ATA_BUSY)
		pr_err("%s: drive still BUSY!\n", drive->name);

	return stat;
}