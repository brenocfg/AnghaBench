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
typedef  enum scsi_host_state { ____Placeholder_scsi_host_state } scsi_host_state ;
struct TYPE_3__ {int value; char* name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* shost_states ; 

const char *scsi_host_state_name(enum scsi_host_state state)
{
	int i;
	char *name = NULL;

	for (i = 0; i < ARRAY_SIZE(shost_states); i++) {
		if (shost_states[i].value == state) {
			name = shost_states[i].name;
			break;
		}
	}
	return name;
}