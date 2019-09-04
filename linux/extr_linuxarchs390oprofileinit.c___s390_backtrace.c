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
 int /*<<< orphan*/  oprofile_add_trace (unsigned long) ; 

__attribute__((used)) static int __s390_backtrace(void *data, unsigned long address, int reliable)
{
	unsigned int *depth = data;

	if (*depth == 0)
		return 1;
	(*depth)--;
	oprofile_add_trace(address);
	return 0;
}