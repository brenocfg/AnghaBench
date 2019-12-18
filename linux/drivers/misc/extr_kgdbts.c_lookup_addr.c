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
 scalar_t__ _do_fork ; 
 scalar_t__ dereference_function_descriptor (void*) ; 
 scalar_t__ do_sys_open ; 
 int /*<<< orphan*/  hw_break_val ; 
 scalar_t__ kgdbts_break_test ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static unsigned long lookup_addr(char *arg)
{
	unsigned long addr = 0;

	if (!strcmp(arg, "kgdbts_break_test"))
		addr = (unsigned long)kgdbts_break_test;
	else if (!strcmp(arg, "sys_open"))
		addr = (unsigned long)do_sys_open;
	else if (!strcmp(arg, "do_fork"))
		addr = (unsigned long)_do_fork;
	else if (!strcmp(arg, "hw_break_val"))
		addr = (unsigned long)&hw_break_val;
	addr = (unsigned long) dereference_function_descriptor((void *)addr);
	return addr;
}