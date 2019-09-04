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
 unsigned int FUNC ; 
 unsigned int OPCODE ; 
 unsigned int RD ; 
 unsigned int RDHWR ; 
 unsigned int RT ; 
 unsigned int SPEC3 ; 
 int /*<<< orphan*/  simulate_rdhwr (struct pt_regs*,int,int) ; 

__attribute__((used)) static int simulate_rdhwr_normal(struct pt_regs *regs, unsigned int opcode)
{
	if ((opcode & OPCODE) == SPEC3 && (opcode & FUNC) == RDHWR) {
		int rd = (opcode & RD) >> 11;
		int rt = (opcode & RT) >> 16;

		simulate_rdhwr(regs, rd, rt);
		return 0;
	}

	/* Not ours.  */
	return -1;
}