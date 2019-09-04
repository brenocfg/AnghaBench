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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ TICKS_PER_JIFFY ; 
 int /*<<< orphan*/  TSTAT ; 
 int /*<<< orphan*/  m68328_tick_cnt ; 
 int /*<<< orphan*/  timer_interrupt (int,void*) ; 

__attribute__((used)) static irqreturn_t hw_tick(int irq, void *dummy)
{
	/* Reset Timer1 */
	TSTAT &= 0;

	m68328_tick_cnt += TICKS_PER_JIFFY;
	return timer_interrupt(irq, dummy);
}