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
 int READ_ONCE (int) ; 
 int /*<<< orphan*/  cmpxchg (int*,int,int) ; 

__attribute__((used)) static int __dm_get_module_param_int(int *module_param, int min, int max)
{
	int param = READ_ONCE(*module_param);
	int modified_param = 0;
	bool modified = true;

	if (param < min)
		modified_param = min;
	else if (param > max)
		modified_param = max;
	else
		modified = false;

	if (modified) {
		(void)cmpxchg(module_param, param, modified_param);
		param = modified_param;
	}

	return param;
}