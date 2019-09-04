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
typedef  unsigned long u32 ;

/* Variables and functions */
 int /*<<< orphan*/  SPR_TTCR ; 
 int /*<<< orphan*/  SPR_TTMR ; 
 unsigned long SPR_TTMR_CR ; 
 unsigned long SPR_TTMR_IE ; 
 unsigned long SPR_TTMR_TP ; 
 unsigned long mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,unsigned long) ; 

inline void openrisc_timer_set_next(unsigned long delta)
{
	u32 c;

	/* Read 32-bit counter value, add delta, mask off the low 28 bits.
	 * We're guaranteed delta won't be bigger than 28 bits because the
	 * generic timekeeping code ensures that for us.
	 */
	c = mfspr(SPR_TTCR);
	c += delta;
	c &= SPR_TTMR_TP;

	/* Set counter and enable interrupt.
	 * Keep timer in continuous mode always.
	 */
	mtspr(SPR_TTMR, SPR_TTMR_CR | SPR_TTMR_IE | c);
}