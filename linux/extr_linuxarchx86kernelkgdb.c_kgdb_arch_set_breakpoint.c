#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kgdb_bkpt {char* saved_instr; int /*<<< orphan*/  type; scalar_t__ bpt_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  gdb_bpt_instr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BP_BREAKPOINT ; 
 int /*<<< orphan*/  BP_POKE_BREAKPOINT ; 
 int BREAK_INSTR_SIZE ; 
 int EBUSY ; 
 int EINVAL ; 
 TYPE_1__ arch_kgdb_ops ; 
 scalar_t__ memcmp (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mutex_is_locked (int /*<<< orphan*/ *) ; 
 int probe_kernel_read (char*,char*,int) ; 
 int probe_kernel_write (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  text_mutex ; 
 int /*<<< orphan*/  text_poke (void*,int /*<<< orphan*/ ,int) ; 

int kgdb_arch_set_breakpoint(struct kgdb_bkpt *bpt)
{
	int err;
	char opc[BREAK_INSTR_SIZE];

	bpt->type = BP_BREAKPOINT;
	err = probe_kernel_read(bpt->saved_instr, (char *)bpt->bpt_addr,
				BREAK_INSTR_SIZE);
	if (err)
		return err;
	err = probe_kernel_write((char *)bpt->bpt_addr,
				 arch_kgdb_ops.gdb_bpt_instr, BREAK_INSTR_SIZE);
	if (!err)
		return err;
	/*
	 * It is safe to call text_poke() because normal kernel execution
	 * is stopped on all cores, so long as the text_mutex is not locked.
	 */
	if (mutex_is_locked(&text_mutex))
		return -EBUSY;
	text_poke((void *)bpt->bpt_addr, arch_kgdb_ops.gdb_bpt_instr,
		  BREAK_INSTR_SIZE);
	err = probe_kernel_read(opc, (char *)bpt->bpt_addr, BREAK_INSTR_SIZE);
	if (err)
		return err;
	if (memcmp(opc, arch_kgdb_ops.gdb_bpt_instr, BREAK_INSTR_SIZE))
		return -EINVAL;
	bpt->type = BP_POKE_BREAKPOINT;

	return err;
}