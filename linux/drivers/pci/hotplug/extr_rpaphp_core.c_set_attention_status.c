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
struct slot {int attention_status; int /*<<< orphan*/  index; } ;
struct hotplug_slot {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DR_INDICATOR ; 
 int rtas_set_indicator (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct slot* to_slot (struct hotplug_slot*) ; 

__attribute__((used)) static int set_attention_status(struct hotplug_slot *hotplug_slot, u8 value)
{
	int rc;
	struct slot *slot = to_slot(hotplug_slot);

	switch (value) {
	case 0:
	case 1:
	case 2:
		break;
	default:
		value = 1;
		break;
	}

	rc = rtas_set_indicator(DR_INDICATOR, slot->index, value);
	if (!rc)
		slot->attention_status = value;

	return rc;
}