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
struct TYPE_4__ {scalar_t__ capacity64; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  hpa_list ; 
 scalar_t__ ide_in_drive_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ idedisk_read_native_max_address (TYPE_1__*,int) ; 

__attribute__((used)) static u64 ide_disk_hpa_get_native_capacity(ide_drive_t *drive, int lba48)
{
	u64 capacity, set_max;

	capacity = drive->capacity64;
	set_max  = idedisk_read_native_max_address(drive, lba48);

	if (ide_in_drive_list(drive->id, hpa_list)) {
		/*
		 * Since we are inclusive wrt to firmware revisions do this
		 * extra check and apply the workaround only when needed.
		 */
		if (set_max == capacity + 1)
			set_max--;
	}

	return set_max;
}