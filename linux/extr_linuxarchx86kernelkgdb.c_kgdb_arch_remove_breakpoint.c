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
struct kgdb_bkpt {scalar_t__ type; scalar_t__ saved_instr; scalar_t__ bpt_addr; } ;

/* Variables and functions */
 scalar_t__ BP_POKE_BREAKPOINT ; 
 int BREAK_INSTR_SIZE ; 
 scalar_t__ memcmp (char*,scalar_t__,int) ; 
 scalar_t__ mutex_is_locked (int /*<<< orphan*/ *) ; 
 int probe_kernel_read (char*,char*,int) ; 
 int probe_kernel_write (char*,char*,int) ; 
 int /*<<< orphan*/  text_mutex ; 
 int /*<<< orphan*/  text_poke (void*,scalar_t__,int) ; 

int kgdb_arch_remove_breakpoint(struct kgdb_bkpt *bpt)
{
	int err;
	char opc[BREAK_INSTR_SIZE];

	if (bpt->type != BP_POKE_BREAKPOINT)
		goto knl_write;
	/*
	 * It is safe to call text_poke() because normal kernel execution
	 * is stopped on all cores, so long as the text_mutex is not locked.
	 */
	if (mutex_is_locked(&text_mutex))
		goto knl_write;
	text_poke((void *)bpt->bpt_addr, bpt->saved_instr, BREAK_INSTR_SIZE);
	err = probe_kernel_read(opc, (char *)bpt->bpt_addr, BREAK_INSTR_SIZE);
	if (err || memcmp(opc, bpt->saved_instr, BREAK_INSTR_SIZE))
		goto knl_write;
	return err;

knl_write:
	return probe_kernel_write((char *)bpt->bpt_addr,
				  (char *)bpt->saved_instr, BREAK_INSTR_SIZE);
}