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
 unsigned int HZ ; 
 int /*<<< orphan*/  barrier () ; 
 int jiffies ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_save_flags (unsigned long) ; 
 scalar_t__ time_before (int,unsigned long) ; 

__attribute__((used)) static void
acornscsi_csdelay(unsigned int cs)
{
    unsigned long target_jiffies, flags;

    target_jiffies = jiffies + 1 + cs * HZ / 100;

    local_save_flags(flags);
    local_irq_enable();

    while (time_before(jiffies, target_jiffies)) barrier();

    local_irq_restore(flags);
}