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
struct task_struct {int dummy; } ;
struct pt_regs {int dummy; } ;
typedef  int /*<<< orphan*/  opcode ;

/* Variables and functions */
 int /*<<< orphan*/  FOLL_FORCE ; 
 int access_process_vm (struct task_struct*,unsigned long,unsigned char*,int,int /*<<< orphan*/ ) ; 
 unsigned long convert_ip_to_linear (struct task_struct*,struct pt_regs*) ; 

__attribute__((used)) static int is_setting_trap_flag(struct task_struct *child, struct pt_regs *regs)
{
	int i, copied;
	unsigned char opcode[15];
	unsigned long addr = convert_ip_to_linear(child, regs);

	copied = access_process_vm(child, addr, opcode, sizeof(opcode),
			FOLL_FORCE);
	for (i = 0; i < copied; i++) {
		switch (opcode[i]) {
		/* popf and iret */
		case 0x9d: case 0xcf:
			return 1;

			/* CHECKME: 64 65 */

		/* opcode and address size prefixes */
		case 0x66: case 0x67:
			continue;
		/* irrelevant prefixes (segment overrides and repeats) */
		case 0x26: case 0x2e:
		case 0x36: case 0x3e:
		case 0x64: case 0x65:
		case 0xf0: case 0xf2: case 0xf3:
			continue;

#ifdef CONFIG_X86_64
		case 0x40 ... 0x4f:
			if (!user_64bit_mode(regs))
				/* 32-bit mode: register increment */
				return 0;
			/* 64-bit mode: REX prefix */
			continue;
#endif

			/* CHECKME: f2, f3 */

		/*
		 * pushf: NOTE! We should probably not let
		 * the user see the TF bit being set. But
		 * it's more pain than it's worth to avoid
		 * it, and a debugger could emulate this
		 * all in user space if it _really_ cares.
		 */
		case 0x9c:
		default:
			return 0;
		}
	}
	return 0;
}