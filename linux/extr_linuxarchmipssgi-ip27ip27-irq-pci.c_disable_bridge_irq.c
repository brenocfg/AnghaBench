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
struct irq_data {int /*<<< orphan*/  irq; } ;
typedef  int /*<<< orphan*/  cpuid_t ;

/* Variables and functions */
 int find_level (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intr_disconnect_level (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void disable_bridge_irq(struct irq_data *d)
{
	cpuid_t cpu;
	int swlevel;

	swlevel = find_level(&cpu, d->irq);	/* Criminal offence */
	intr_disconnect_level(cpu, swlevel);
}