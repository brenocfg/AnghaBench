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
struct qm1d1c0042_state {int* regs; } ;

/* Variables and functions */
 int reg_write (struct qm1d1c0042_state*,int,int) ; 

__attribute__((used)) static int qm1d1c0042_set_srch_mode(struct qm1d1c0042_state *state, bool fast)
{
	if (fast)
		state->regs[0x03] |= 0x01; /* set fast search mode */
	else
		state->regs[0x03] &= ~0x01 & 0xff;

	return reg_write(state, 0x03, state->regs[0x03]);
}