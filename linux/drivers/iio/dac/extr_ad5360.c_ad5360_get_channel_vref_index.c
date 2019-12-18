#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ad5360_state {TYPE_1__* chip_info; } ;
struct TYPE_2__ {unsigned int channels_per_group; unsigned int num_vrefs; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int ad5360_get_channel_vref_index(struct ad5360_state *st,
	unsigned int channel)
{
	unsigned int i;

	/* The first groups have their own vref, while the remaining groups
	 * share the last vref */
	i = channel / st->chip_info->channels_per_group;
	if (i >= st->chip_info->num_vrefs)
		i = st->chip_info->num_vrefs - 1;

	return i;
}