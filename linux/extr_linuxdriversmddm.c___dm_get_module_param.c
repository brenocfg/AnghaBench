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
 unsigned int READ_ONCE (unsigned int) ; 
 int /*<<< orphan*/  cmpxchg (unsigned int*,unsigned int,unsigned int) ; 

unsigned __dm_get_module_param(unsigned *module_param,
			       unsigned def, unsigned max)
{
	unsigned param = READ_ONCE(*module_param);
	unsigned modified_param = 0;

	if (!param)
		modified_param = def;
	else if (param > max)
		modified_param = max;

	if (modified_param) {
		(void)cmpxchg(module_param, param, modified_param);
		param = modified_param;
	}

	return param;
}