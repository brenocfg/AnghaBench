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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 unsigned short STEP_OPCODE ; 
 int /*<<< orphan*/  __raw_readw (long) ; 
 int /*<<< orphan*/  flush_icache_range (long,scalar_t__) ; 
 unsigned short* get_step_address (struct pt_regs*) ; 
 scalar_t__ instruction_size (int /*<<< orphan*/ ) ; 
 int stepped_address ; 
 int /*<<< orphan*/  stepped_opcode ; 

__attribute__((used)) static void do_single_step(struct pt_regs *linux_regs)
{
	/* Determine where the target instruction will send us to */
	unsigned short *addr = get_step_address(linux_regs);

	stepped_address = (int)addr;

	/* Replace it */
	stepped_opcode = __raw_readw((long)addr);
	*addr = STEP_OPCODE;

	/* Flush and return */
	flush_icache_range((long)addr, (long)addr +
			   instruction_size(stepped_opcode));
}