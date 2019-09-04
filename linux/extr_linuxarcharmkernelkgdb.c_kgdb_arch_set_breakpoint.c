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
struct kgdb_bkpt {scalar_t__ bpt_addr; int /*<<< orphan*/  saved_instr; } ;
struct TYPE_2__ {scalar_t__ gdb_bpt_instr; } ;

/* Variables and functions */
 int BREAK_INSTR_SIZE ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  __patch_text (void*,unsigned int) ; 
 TYPE_1__ arch_kgdb_ops ; 
 int probe_kernel_read (int /*<<< orphan*/ ,char*,int) ; 

int kgdb_arch_set_breakpoint(struct kgdb_bkpt *bpt)
{
	int err;

	/* patch_text() only supports int-sized breakpoints */
	BUILD_BUG_ON(sizeof(int) != BREAK_INSTR_SIZE);

	err = probe_kernel_read(bpt->saved_instr, (char *)bpt->bpt_addr,
				BREAK_INSTR_SIZE);
	if (err)
		return err;

	/* Machine is already stopped, so we can use __patch_text() directly */
	__patch_text((void *)bpt->bpt_addr,
		     *(unsigned int *)arch_kgdb_ops.gdb_bpt_instr);

	return err;
}