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
 int /*<<< orphan*/  BREAK_INSTR_SIZE ; 
 int /*<<< orphan*/  fill_get_buf (int /*<<< orphan*/ ) ; 
 unsigned long lookup_addr (char*) ; 
 int /*<<< orphan*/  scratch_buf ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void break_helper(char *bp_type, char *arg, unsigned long vaddr)
{
	unsigned long addr;

	if (arg)
		addr = lookup_addr(arg);
	else
		addr = vaddr;

	sprintf(scratch_buf, "%s,%lx,%i", bp_type, addr,
		BREAK_INSTR_SIZE);
	fill_get_buf(scratch_buf);
}