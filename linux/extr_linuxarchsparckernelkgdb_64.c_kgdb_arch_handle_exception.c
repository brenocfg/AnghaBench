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
struct pt_regs {unsigned long tpc; unsigned long tnpc; } ;

/* Variables and functions */
 scalar_t__ arch_kgdb_breakpoint ; 
 int /*<<< orphan*/  kgdb_hex2long (char**,unsigned long*) ; 

int kgdb_arch_handle_exception(int e_vector, int signo, int err_code,
			       char *remcomInBuffer, char *remcomOutBuffer,
			       struct pt_regs *linux_regs)
{
	unsigned long addr;
	char *ptr;

	switch (remcomInBuffer[0]) {
	case 'c':
		/* try to read optional parameter, pc unchanged if no parm */
		ptr = &remcomInBuffer[1];
		if (kgdb_hex2long(&ptr, &addr)) {
			linux_regs->tpc = addr;
			linux_regs->tnpc = addr + 4;
		}
		/* fall through */

	case 'D':
	case 'k':
		if (linux_regs->tpc == (unsigned long) arch_kgdb_breakpoint) {
			linux_regs->tpc = linux_regs->tnpc;
			linux_regs->tnpc += 4;
		}
		return 0;
	}
	return -1;
}