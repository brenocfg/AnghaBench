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
 scalar_t__ WARN_ON (int) ; 
 int get_evtchn_to_irq (unsigned int) ; 
 int /*<<< orphan*/  unbind_from_irq (int) ; 

void evtchn_put(unsigned int evtchn)
{
	int irq = get_evtchn_to_irq(evtchn);
	if (WARN_ON(irq == -1))
		return;
	unbind_from_irq(irq);
}