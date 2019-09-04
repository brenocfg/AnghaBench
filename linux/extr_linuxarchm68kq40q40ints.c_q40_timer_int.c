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
 unsigned char* DAC_LEFT ; 
 unsigned char* DAC_RIGHT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int SVOL ; 
 int /*<<< orphan*/  q40_timer_routine (int,void*) ; 
 int ql_ticks ; 
 int sound_ticks ; 

__attribute__((used)) static irqreturn_t q40_timer_int (int irq, void * dev)
{
	ql_ticks = ql_ticks ? 0 : 1;
	if (sound_ticks) {
		unsigned char sval=(sound_ticks & 1) ? 128-SVOL : 128+SVOL;
		sound_ticks--;
		*DAC_LEFT=sval;
		*DAC_RIGHT=sval;
	}

	if (!ql_ticks)
		q40_timer_routine(irq, dev);
	return IRQ_HANDLED;
}