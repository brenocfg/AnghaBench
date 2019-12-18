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
typedef  scalar_t__ u64 ;
struct TYPE_4__ {scalar_t__ capacity64; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 scalar_t__ idedisk_set_max_address (TYPE_1__*,scalar_t__,int) ; 

__attribute__((used)) static u64 ide_disk_hpa_set_capacity(ide_drive_t *drive, u64 set_max, int lba48)
{
	set_max = idedisk_set_max_address(drive, set_max, lba48);
	if (set_max)
		drive->capacity64 = set_max;

	return set_max;
}