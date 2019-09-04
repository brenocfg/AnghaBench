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
 int /*<<< orphan*/  KS8695_CLOCK_RATE ; 
 scalar_t__ KS8695_TMCON ; 
 scalar_t__ KS8695_TMR_VA ; 
 unsigned long TMCON_T0EN ; 
 unsigned long TMCON_T1EN ; 
 int /*<<< orphan*/  clockevent_ks8695 ; 
 int /*<<< orphan*/  clockevents_config_and_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 unsigned long readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned long,scalar_t__) ; 

__attribute__((used)) static void ks8695_timer_setup(void)
{
	unsigned long tmcon;

	/* Disable timer 0 and 1 */
	tmcon = readl_relaxed(KS8695_TMR_VA + KS8695_TMCON);
	tmcon &= ~TMCON_T0EN;
	tmcon &= ~TMCON_T1EN;
	writel_relaxed(tmcon, KS8695_TMR_VA + KS8695_TMCON);

	/*
	 * Use timer 1 to fire IRQs on the timeline, minimum 2 cycles
	 * (one on each counter) maximum 2*2^32, but the API will only
	 * accept up to a 32bit full word (0xFFFFFFFFU).
	 */
	clockevents_config_and_register(&clockevent_ks8695,
					KS8695_CLOCK_RATE, 2,
					0xFFFFFFFFU);
}