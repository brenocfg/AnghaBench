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
struct hotplug_slot {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int get_adapter_status(struct hotplug_slot *hotplug_slot, u8 *value)
{
	/* if the slot exits it always contains a function */
	*value = 1;
	return 0;
}