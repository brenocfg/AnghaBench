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
 int /*<<< orphan*/  bus_error_jmp ; 
 int catch_memory_errors ; 
 char* kallsyms_lookup (unsigned long,unsigned long*,unsigned long*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync () ; 
 int /*<<< orphan*/  tmpstr ; 

__attribute__((used)) static void get_function_bounds(unsigned long pc, unsigned long *startp,
				unsigned long *endp)
{
	unsigned long size, offset;
	const char *name;

	*startp = *endp = 0;
	if (pc == 0)
		return;
	if (setjmp(bus_error_jmp) == 0) {
		catch_memory_errors = 1;
		sync();
		name = kallsyms_lookup(pc, &size, &offset, NULL, tmpstr);
		if (name != NULL) {
			*startp = pc - offset;
			*endp = pc - offset + size;
		}
		sync();
	}
	catch_memory_errors = 0;
}