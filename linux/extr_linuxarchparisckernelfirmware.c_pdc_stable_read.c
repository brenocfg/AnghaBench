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
 int /*<<< orphan*/  PDC_STABLE ; 
 int /*<<< orphan*/  PDC_STABLE_READ ; 
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_to_wide (int /*<<< orphan*/ ) ; 
 int mem_pdc_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  pdc_lock ; 
 int /*<<< orphan*/  pdc_result ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int pdc_stable_read(unsigned long staddr, void *memaddr, unsigned long count)
{
       int retval;
	unsigned long flags;

       spin_lock_irqsave(&pdc_lock, flags);
       retval = mem_pdc_call(PDC_STABLE, PDC_STABLE_READ, staddr,
               __pa(pdc_result), count);
       convert_to_wide(pdc_result);
       memcpy(memaddr, pdc_result, count);
       spin_unlock_irqrestore(&pdc_lock, flags);

       return retval;
}