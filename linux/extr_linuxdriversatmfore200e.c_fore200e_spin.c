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
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static void
fore200e_spin(int msecs)
{
    unsigned long timeout = jiffies + msecs_to_jiffies(msecs);
    while (time_before(jiffies, timeout));
}