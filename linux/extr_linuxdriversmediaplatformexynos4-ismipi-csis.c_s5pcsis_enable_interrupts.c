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
typedef  int /*<<< orphan*/  u32 ;
struct csis_state {int /*<<< orphan*/  interrupt_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  S5PCSIS_INTMSK ; 
 int /*<<< orphan*/  s5pcsis_read (struct csis_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5pcsis_write (struct csis_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s5pcsis_enable_interrupts(struct csis_state *state, bool on)
{
	u32 val = s5pcsis_read(state, S5PCSIS_INTMSK);
	if (on)
		val |= state->interrupt_mask;
	else
		val &= ~state->interrupt_mask;
	s5pcsis_write(state, S5PCSIS_INTMSK, val);
}