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
 int late_i915_load ; 

void
ips_link_to_i915_driver(void)
{
	/* We can't cleanly get at the various ips_driver structs from
	 * this caller (the i915 driver), so just set a flag saying
	 * that it's time to try getting the symbols again.
	 */
	late_i915_load = true;
}