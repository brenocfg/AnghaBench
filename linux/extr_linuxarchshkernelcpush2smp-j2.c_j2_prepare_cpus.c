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
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_PERCPU ; 
 unsigned int NR_CPUS ; 
 int /*<<< orphan*/  irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 scalar_t__ j2_ipi_interrupt_handler ; 
 int /*<<< orphan*/  j2_ipi_irq ; 
 void* j2_ipi_trigger ; 
 struct device_node* of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 void* of_iomap (struct device_node*,int /*<<< orphan*/ ) ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  set_cpu_possible (unsigned int,int) ; 
 int /*<<< orphan*/  set_cpu_present (unsigned int,int) ; 
 void* sh2_cpuid_addr ; 

__attribute__((used)) static void j2_prepare_cpus(unsigned int max_cpus)
{
	struct device_node *np;
	unsigned i, max = 1;

	np = of_find_compatible_node(NULL, NULL, "jcore,ipi-controller");
	if (!np)
		goto out;

	j2_ipi_irq = irq_of_parse_and_map(np, 0);
	j2_ipi_trigger = of_iomap(np, 0);
	if (!j2_ipi_irq || !j2_ipi_trigger)
		goto out;

	np = of_find_compatible_node(NULL, NULL, "jcore,cpuid-mmio");
	if (!np)
		goto out;

	sh2_cpuid_addr = of_iomap(np, 0);
	if (!sh2_cpuid_addr)
		goto out;

	if (request_irq(j2_ipi_irq, j2_ipi_interrupt_handler, IRQF_PERCPU,
			"ipi", (void *)j2_ipi_interrupt_handler) != 0)
		goto out;

	max = max_cpus;
out:
	/* Disable any cpus past max_cpus, or all secondaries if we didn't
	 * get the necessary resources to support SMP. */
	for (i=max; i<NR_CPUS; i++) {
		set_cpu_possible(i, false);
		set_cpu_present(i, false);
	}
}