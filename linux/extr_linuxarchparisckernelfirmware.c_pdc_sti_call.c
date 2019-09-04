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
 int /*<<< orphan*/  pdc_lock ; 
 int real32_call (unsigned long,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int pdc_sti_call(unsigned long func, unsigned long flags,
                 unsigned long inptr, unsigned long outputr,
                 unsigned long glob_cfg)
{
        int retval;
	unsigned long irqflags;

        spin_lock_irqsave(&pdc_lock, irqflags);  
        retval = real32_call(func, flags, inptr, outputr, glob_cfg);
        spin_unlock_irqrestore(&pdc_lock, irqflags);

        return retval;
}