#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  drive_whitelist ; 
 int ide_in_drive_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ide_dma_good_drive(ide_drive_t *drive)
{
	return ide_in_drive_list(drive->id, drive_whitelist);
}