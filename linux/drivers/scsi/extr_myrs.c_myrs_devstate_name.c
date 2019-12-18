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
struct myrs_devstate_name_entry {int state; char* name; } ;
typedef  enum myrs_devstate { ____Placeholder_myrs_devstate } myrs_devstate ;

/* Variables and functions */
 int ARRAY_SIZE (struct myrs_devstate_name_entry*) ; 
 struct myrs_devstate_name_entry* myrs_devstate_name_list ; 

__attribute__((used)) static char *myrs_devstate_name(enum myrs_devstate state)
{
	struct myrs_devstate_name_entry *entry = myrs_devstate_name_list;
	int i;

	for (i = 0; i < ARRAY_SIZE(myrs_devstate_name_list); i++) {
		if (entry[i].state == state)
			return entry[i].name;
	}
	return NULL;
}