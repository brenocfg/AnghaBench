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
typedef  int u8 ;
struct slot {int state; } ;
struct hotplug_slot {int dummy; } ;

/* Variables and functions */
 int EMPTY ; 
 int NOT_VALID ; 
 int PRESENT ; 
 int rpaphp_get_sensor_state (struct slot*,int*) ; 
 struct slot* to_slot (struct hotplug_slot*) ; 

__attribute__((used)) static int get_adapter_status(struct hotplug_slot *hotplug_slot, u8 *value)
{
	struct slot *slot = to_slot(hotplug_slot);
	int rc, state;

	rc = rpaphp_get_sensor_state(slot, &state);

	*value = NOT_VALID;
	if (rc)
		return rc;

	if (state == EMPTY)
		*value = EMPTY;
	else if (state == PRESENT)
		*value = slot->state;

	return 0;
}