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
struct pt_regs {unsigned long pc; } ;

/* Variables and functions */
 int /*<<< orphan*/  kgdb_hex2long (char**,unsigned long*) ; 

int kgdb_arch_handle_exception(int vector, int signo, int err_code,
			       char *remcom_in_buffer, char *remcom_out_buffer,
			       struct pt_regs *regs)
{
	char *ptr;
	unsigned long address;

	switch (remcom_in_buffer[0]) {
	case 'c':
		/* handle the optional parameter */
		ptr = &remcom_in_buffer[1];
		if (kgdb_hex2long(&ptr, &address))
			regs->pc = address;

		return 0;
	}
	return -1; /* this means that we do not want to exit from the handler */
}