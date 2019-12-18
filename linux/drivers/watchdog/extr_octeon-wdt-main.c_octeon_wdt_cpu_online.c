#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int mode; int /*<<< orphan*/  len; } ;
union cvmx_ciu_wdogx {int u64; TYPE_1__ s; } ;
typedef  scalar_t__ u64 ;
struct irq_domain {int dummy; } ;
typedef  int /*<<< orphan*/  cpumask_t ;
struct TYPE_4__ {scalar_t__ target_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_CIU_PP_POKEX (unsigned int) ; 
 int /*<<< orphan*/  CVMX_CIU_WDOGX (unsigned int) ; 
 int /*<<< orphan*/  IRQF_NO_THREAD ; 
 int /*<<< orphan*/  IRQ_TYPE_EDGE_RISING ; 
 int /*<<< orphan*/  OCTEON_FEATURE_CIU3 ; 
 unsigned int OCTEON_IRQ_WDOG0 ; 
 int WD_BLOCK_NUMBER ; 
 int /*<<< orphan*/  countdown_reset ; 
 unsigned int cpu2core (unsigned int) ; 
 int cpu_to_node (unsigned int) ; 
 int /*<<< orphan*/  cpumask_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_set_cpu (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvmx_write_csr_node (int,int /*<<< orphan*/ ,int) ; 
 unsigned int irq_create_mapping (struct irq_domain*,int) ; 
 int /*<<< orphan*/  irq_enabled_cpus ; 
 int /*<<< orphan*/  irq_get_irq_data (unsigned int) ; 
 int /*<<< orphan*/  irq_set_affinity (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irqd_set_trigger_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ octeon_has_feature (int /*<<< orphan*/ ) ; 
 struct irq_domain* octeon_irq_get_block_domain (int,int) ; 
 TYPE_2__* octeon_wdt_bootvector ; 
 scalar_t__ octeon_wdt_nmi_stage2 ; 
 int /*<<< orphan*/  octeon_wdt_poke_irq ; 
 int /*<<< orphan*/  panic (char*,unsigned int) ; 
 int /*<<< orphan*/ * per_cpu_countdown ; 
 scalar_t__ request_irq (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timeout_cnt ; 

__attribute__((used)) static int octeon_wdt_cpu_online(unsigned int cpu)
{
	unsigned int core;
	unsigned int irq;
	union cvmx_ciu_wdogx ciu_wdog;
	int node;
	struct irq_domain *domain;
	int hwirq;

	core = cpu2core(cpu);
	node = cpu_to_node(cpu);

	octeon_wdt_bootvector[core].target_ptr = (u64)octeon_wdt_nmi_stage2;

	/* Disable it before doing anything with the interrupts. */
	ciu_wdog.u64 = 0;
	cvmx_write_csr_node(node, CVMX_CIU_WDOGX(core), ciu_wdog.u64);

	per_cpu_countdown[cpu] = countdown_reset;

	if (octeon_has_feature(OCTEON_FEATURE_CIU3)) {
		/* Must get the domain for the watchdog block */
		domain = octeon_irq_get_block_domain(node, WD_BLOCK_NUMBER);

		/* Get a irq for the wd intsn (hardware interrupt) */
		hwirq = WD_BLOCK_NUMBER << 12 | 0x200 | core;
		irq = irq_create_mapping(domain, hwirq);
		irqd_set_trigger_type(irq_get_irq_data(irq),
				      IRQ_TYPE_EDGE_RISING);
	} else
		irq = OCTEON_IRQ_WDOG0 + core;

	if (request_irq(irq, octeon_wdt_poke_irq,
			IRQF_NO_THREAD, "octeon_wdt", octeon_wdt_poke_irq))
		panic("octeon_wdt: Couldn't obtain irq %d", irq);

	/* Must set the irq affinity here */
	if (octeon_has_feature(OCTEON_FEATURE_CIU3)) {
		cpumask_t mask;

		cpumask_clear(&mask);
		cpumask_set_cpu(cpu, &mask);
		irq_set_affinity(irq, &mask);
	}

	cpumask_set_cpu(cpu, &irq_enabled_cpus);

	/* Poke the watchdog to clear out its state */
	cvmx_write_csr_node(node, CVMX_CIU_PP_POKEX(core), 1);

	/* Finally enable the watchdog now that all handlers are installed */
	ciu_wdog.u64 = 0;
	ciu_wdog.s.len = timeout_cnt;
	ciu_wdog.s.mode = 3;	/* 3 = Interrupt + NMI + Soft-Reset */
	cvmx_write_csr_node(node, CVMX_CIU_WDOGX(core), ciu_wdog.u64);

	return 0;
}