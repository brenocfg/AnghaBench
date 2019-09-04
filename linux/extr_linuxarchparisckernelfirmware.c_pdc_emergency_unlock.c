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
 scalar_t__ spin_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void pdc_emergency_unlock(void)
{
 	/* Spinlock DEBUG code freaks out if we unconditionally unlock */
        if (spin_is_locked(&pdc_lock))
		spin_unlock(&pdc_lock);
}