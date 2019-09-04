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
 int EINVAL ; 
 unsigned long NUM_GPRS ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 

int regs_query_register_offset(const char *name)
{
	unsigned long offset;

	if (!name || *name != 'r')
		return -EINVAL;
	if (kstrtoul(name + 1, 10, &offset))
		return -EINVAL;
	if (offset >= NUM_GPRS)
		return -EINVAL;
	return offset;
}