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
 char* REG ; 
 int /*<<< orphan*/  __delay (int) ; 
 int /*<<< orphan*/  bus_error_jmp ; 
 int catch_memory_errors ; 
 char* kallsyms_lookup (unsigned long,unsigned long*,unsigned long*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync () ; 
 int /*<<< orphan*/  tmpstr ; 

__attribute__((used)) static void xmon_print_symbol(unsigned long address, const char *mid,
			      const char *after)
{
	char *modname;
	const char *name = NULL;
	unsigned long offset, size;

	printf(REG, address);
	if (setjmp(bus_error_jmp) == 0) {
		catch_memory_errors = 1;
		sync();
		name = kallsyms_lookup(address, &size, &offset, &modname,
				       tmpstr);
		sync();
		/* wait a little while to see if we get a machine check */
		__delay(200);
	}

	catch_memory_errors = 0;

	if (name) {
		printf("%s%s+%#lx/%#lx", mid, name, offset, size);
		if (modname)
			printf(" [%s]", modname);
	}
	printf("%s", after);
}