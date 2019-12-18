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
struct qman_portal {int dummy; } ;
struct qm_portal_config {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 struct qman_portal** affine_portals ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 unsigned int cpumask_any_but (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  cpumask_of (unsigned int) ; 
 int /*<<< orphan*/  irq_set_affinity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct qm_portal_config* qman_get_qm_portal_config (struct qman_portal*) ; 
 int /*<<< orphan*/  qman_portal_update_sdest (struct qm_portal_config const*,unsigned int) ; 

__attribute__((used)) static int qman_offline_cpu(unsigned int cpu)
{
	struct qman_portal *p;
	const struct qm_portal_config *pcfg;

	p = affine_portals[cpu];
	if (p) {
		pcfg = qman_get_qm_portal_config(p);
		if (pcfg) {
			/* select any other online CPU */
			cpu = cpumask_any_but(cpu_online_mask, cpu);
			irq_set_affinity(pcfg->irq, cpumask_of(cpu));
			qman_portal_update_sdest(pcfg, cpu);
		}
	}
	return 0;
}