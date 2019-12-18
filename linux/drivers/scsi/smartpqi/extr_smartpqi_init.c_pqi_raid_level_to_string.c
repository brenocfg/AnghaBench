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
typedef  size_t u8 ;

/* Variables and functions */
 size_t ARRAY_SIZE (char**) ; 
 char** raid_levels ; 

__attribute__((used)) static char *pqi_raid_level_to_string(u8 raid_level)
{
	if (raid_level < ARRAY_SIZE(raid_levels))
		return raid_levels[raid_level];

	return "RAID UNKNOWN";
}