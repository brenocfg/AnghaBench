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
 int /*<<< orphan*/  PERF_COUNT_SW_EMULATION_FAULTS ; 
 unsigned int SPEC0 ; 
 unsigned int SYNC ; 
 int /*<<< orphan*/  perf_sw_event (int /*<<< orphan*/ ,int,struct pt_regs*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int simulate_sync(struct pt_regs *regs, unsigned int opcode)
{
	if ((opcode & OPCODE) == SPEC0 && (opcode & FUNC) == SYNC) {
		perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS,
				1, regs, 0);
		return 0;
	}

	return -1;			/* Must be something else ... */
}