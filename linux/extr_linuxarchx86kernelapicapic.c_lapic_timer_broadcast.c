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
struct cpumask {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void lapic_timer_broadcast(const struct cpumask *mask)
{
#ifdef CONFIG_SMP
	apic->send_IPI_mask(mask, LOCAL_TIMER_VECTOR);
#endif
}