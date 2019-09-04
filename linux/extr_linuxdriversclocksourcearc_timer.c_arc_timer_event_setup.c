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
 int /*<<< orphan*/  ARC_REG_TIMER0_CNT ; 
 int /*<<< orphan*/  ARC_REG_TIMER0_CTRL ; 
 int /*<<< orphan*/  ARC_REG_TIMER0_LIMIT ; 
 unsigned int TIMER_CTRL_IE ; 
 unsigned int TIMER_CTRL_NH ; 
 int /*<<< orphan*/  write_aux_reg (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void arc_timer_event_setup(unsigned int cycles)
{
	write_aux_reg(ARC_REG_TIMER0_LIMIT, cycles);
	write_aux_reg(ARC_REG_TIMER0_CNT, 0);	/* start from 0 */

	write_aux_reg(ARC_REG_TIMER0_CTRL, TIMER_CTRL_IE | TIMER_CTRL_NH);
}