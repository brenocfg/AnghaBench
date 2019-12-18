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

/* Variables and functions */
 unsigned int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int* context_switch_events ; 

__attribute__((used)) static int ring_id_to_context_switch_event(unsigned int ring_id)
{
	if (WARN_ON(ring_id >= ARRAY_SIZE(context_switch_events)))
		return -EINVAL;

	return context_switch_events[ring_id];
}