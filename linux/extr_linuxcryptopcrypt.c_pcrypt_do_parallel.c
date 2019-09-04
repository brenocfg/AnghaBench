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
struct pcrypt_cpumask {int /*<<< orphan*/  mask; } ;
struct padata_priv {int dummy; } ;
struct padata_pcrypt {int /*<<< orphan*/  pinst; int /*<<< orphan*/  cb_cpumask; } ;

/* Variables and functions */
 unsigned int cpumask_first (int /*<<< orphan*/ ) ; 
 unsigned int cpumask_next (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ cpumask_test_cpu (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int cpumask_weight (int /*<<< orphan*/ ) ; 
 int padata_do_parallel (int /*<<< orphan*/ ,struct padata_priv*,unsigned int) ; 
 struct pcrypt_cpumask* rcu_dereference_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock_bh () ; 
 int /*<<< orphan*/  rcu_read_unlock_bh () ; 

__attribute__((used)) static int pcrypt_do_parallel(struct padata_priv *padata, unsigned int *cb_cpu,
			      struct padata_pcrypt *pcrypt)
{
	unsigned int cpu_index, cpu, i;
	struct pcrypt_cpumask *cpumask;

	cpu = *cb_cpu;

	rcu_read_lock_bh();
	cpumask = rcu_dereference_bh(pcrypt->cb_cpumask);
	if (cpumask_test_cpu(cpu, cpumask->mask))
			goto out;

	if (!cpumask_weight(cpumask->mask))
			goto out;

	cpu_index = cpu % cpumask_weight(cpumask->mask);

	cpu = cpumask_first(cpumask->mask);
	for (i = 0; i < cpu_index; i++)
		cpu = cpumask_next(cpu, cpumask->mask);

	*cb_cpu = cpu;

out:
	rcu_read_unlock_bh();
	return padata_do_parallel(pcrypt->pinst, padata, cpu);
}