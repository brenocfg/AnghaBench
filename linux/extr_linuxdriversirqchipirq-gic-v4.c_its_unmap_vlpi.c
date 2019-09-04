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
 int /*<<< orphan*/  IRQ_DISABLE_UNLAZY ; 
 int /*<<< orphan*/  irq_clear_status_flags (int,int /*<<< orphan*/ ) ; 
 int irq_set_vcpu_affinity (int,int /*<<< orphan*/ *) ; 

int its_unmap_vlpi(int irq)
{
	irq_clear_status_flags(irq, IRQ_DISABLE_UNLAZY);
	return irq_set_vcpu_affinity(irq, NULL);
}