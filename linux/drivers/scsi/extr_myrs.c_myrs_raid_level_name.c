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
struct myrs_raid_level_name_entry {int level; char* name; } ;
typedef  enum myrs_raid_level { ____Placeholder_myrs_raid_level } myrs_raid_level ;

/* Variables and functions */
 int ARRAY_SIZE (struct myrs_raid_level_name_entry*) ; 
 struct myrs_raid_level_name_entry* myrs_raid_level_name_list ; 

__attribute__((used)) static char *myrs_raid_level_name(enum myrs_raid_level level)
{
	struct myrs_raid_level_name_entry *entry = myrs_raid_level_name_list;
	int i;

	for (i = 0; i < ARRAY_SIZE(myrs_raid_level_name_list); i++) {
		if (entry[i].level == level)
			return entry[i].name;
	}
	return NULL;
}