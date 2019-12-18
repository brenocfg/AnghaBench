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
struct pcmcia_align_data {int mask; int offset; } ;
typedef  int resource_size_t ;

/* Variables and functions */

__attribute__((used)) static resource_size_t pcmcia_common_align(struct pcmcia_align_data *align_data,
					resource_size_t start)
{
	resource_size_t ret;
	/*
	 * Ensure that we have the correct start address
	 */
	ret = (start & ~align_data->mask) + align_data->offset;
	if (ret < start)
		ret += align_data->mask + 1;
	return ret;
}