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
 int /*<<< orphan*/  PDC_BROADCAST_RESET ; 
 int /*<<< orphan*/  PDC_DO_RESET ; 
 int mem_pdc_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdc_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int pdc_do_reset(void)
{
        int retval;
	unsigned long flags;

        spin_lock_irqsave(&pdc_lock, flags);
        retval = mem_pdc_call(PDC_BROADCAST_RESET, PDC_DO_RESET);
        spin_unlock_irqrestore(&pdc_lock, flags);

        return retval;
}