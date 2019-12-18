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
struct myrb_raidlevel_name_entry {int level; char const* name; } ;
typedef  enum myrb_raidlevel { ____Placeholder_myrb_raidlevel } myrb_raidlevel ;

/* Variables and functions */
 int ARRAY_SIZE (struct myrb_raidlevel_name_entry*) ; 
 struct myrb_raidlevel_name_entry* myrb_raidlevel_name_list ; 

__attribute__((used)) static const char *myrb_raidlevel_name(enum myrb_raidlevel level)
{
	struct myrb_raidlevel_name_entry *entry = myrb_raidlevel_name_list;
	int i;

	for (i = 0; i < ARRAY_SIZE(myrb_raidlevel_name_list); i++) {
		if (entry[i].level == level)
			return entry[i].name;
	}
	return NULL;
}