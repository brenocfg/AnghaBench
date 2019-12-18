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
 int EOVERFLOW ; 

__attribute__((used)) static int altera_check_stack(int stack_ptr, int count, int *status)
{
	if (stack_ptr < count) {
		*status = -EOVERFLOW;
		return 0;
	}

	return 1;
}