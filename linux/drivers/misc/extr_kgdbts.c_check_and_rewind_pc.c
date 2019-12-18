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
 unsigned long BREAK_INSTR_SIZE ; 
 int /*<<< orphan*/  NUMREGBYTES ; 
 scalar_t__ arch_needs_sstep_emulation ; 
 unsigned long cont_addr ; 
 int /*<<< orphan*/  eprintk (char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  gdb_regs_to_pt_regs (scalar_t__,int /*<<< orphan*/ *) ; 
 unsigned long instruction_pointer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  instruction_pointer_set (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  kgdb_hex2mem (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ kgdbts_gdb_regs ; 
 int /*<<< orphan*/  kgdbts_regs ; 
 unsigned long lookup_addr (char*) ; 
 int restart_from_top_after_write ; 
 unsigned long sstep_addr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  v2printk (char*,...) ; 

__attribute__((used)) static int check_and_rewind_pc(char *put_str, char *arg)
{
	unsigned long addr = lookup_addr(arg);
	unsigned long ip;
	int offset = 0;

	kgdb_hex2mem(&put_str[1], (char *)kgdbts_gdb_regs,
		 NUMREGBYTES);
	gdb_regs_to_pt_regs(kgdbts_gdb_regs, &kgdbts_regs);
	ip = instruction_pointer(&kgdbts_regs);
	v2printk("Stopped at IP: %lx\n", ip);
#ifdef GDB_ADJUSTS_BREAK_OFFSET
	/* On some arches, a breakpoint stop requires it to be decremented */
	if (addr + BREAK_INSTR_SIZE == ip)
		offset = -BREAK_INSTR_SIZE;
#endif

	if (arch_needs_sstep_emulation && sstep_addr &&
	    ip + offset == sstep_addr &&
	    ((!strcmp(arg, "sys_open") || !strcmp(arg, "do_fork")))) {
		/* This is special case for emulated single step */
		v2printk("Emul: rewind hit single step bp\n");
		restart_from_top_after_write = 1;
	} else if (strcmp(arg, "silent") && ip + offset != addr) {
		eprintk("kgdbts: BP mismatch %lx expected %lx\n",
			   ip + offset, addr);
		return 1;
	}
	/* Readjust the instruction pointer if needed */
	ip += offset;
	cont_addr = ip;
#ifdef GDB_ADJUSTS_BREAK_OFFSET
	instruction_pointer_set(&kgdbts_regs, ip);
#endif
	return 0;
}