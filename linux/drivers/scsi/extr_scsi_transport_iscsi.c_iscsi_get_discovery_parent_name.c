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
struct TYPE_3__ {int value; char* name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* iscsi_discovery_parent_names ; 

char *iscsi_get_discovery_parent_name(int parent_type)
{
	int i;
	char *state = "Unknown!";

	for (i = 0; i < ARRAY_SIZE(iscsi_discovery_parent_names); i++) {
		if (iscsi_discovery_parent_names[i].value & parent_type) {
			state = iscsi_discovery_parent_names[i].name;
			break;
		}
	}
	return state;
}