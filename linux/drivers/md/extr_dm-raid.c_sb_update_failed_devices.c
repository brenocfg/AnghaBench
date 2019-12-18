#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct dm_raid_superblock {void** extended_failed_devices; void* failed_devices; } ;

/* Variables and functions */
 int ARRAY_SIZE (void**) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sb_update_failed_devices(struct dm_raid_superblock *sb, uint64_t *failed_devices)
{
	int i = ARRAY_SIZE(sb->extended_failed_devices);

	sb->failed_devices = cpu_to_le64(failed_devices[0]);
	while (i--)
		sb->extended_failed_devices[i] = cpu_to_le64(failed_devices[i+1]);
}