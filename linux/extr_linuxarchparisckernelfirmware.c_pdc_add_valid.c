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
 int /*<<< orphan*/  PDC_ADD_VALID ; 
 int /*<<< orphan*/  PDC_ADD_VALID_VERIFY ; 
 int mem_pdc_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  pdc_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int pdc_add_valid(unsigned long address)
{
        int retval;
	unsigned long flags;

        spin_lock_irqsave(&pdc_lock, flags);
        retval = mem_pdc_call(PDC_ADD_VALID, PDC_ADD_VALID_VERIFY, address);
        spin_unlock_irqrestore(&pdc_lock, flags);

        return retval;
}