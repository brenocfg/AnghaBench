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
struct rdtgroup {int dummy; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 scalar_t__ cpumask_test_cpu (int,struct cpumask const*) ; 
 int get_cpu () ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  smp_call_function_many (struct cpumask const*,int /*<<< orphan*/  (*) (struct rdtgroup*),struct rdtgroup*,int) ; 
 int /*<<< orphan*/  update_cpu_closid_rmid (struct rdtgroup*) ; 

__attribute__((used)) static void
update_closid_rmid(const struct cpumask *cpu_mask, struct rdtgroup *r)
{
	int cpu = get_cpu();

	if (cpumask_test_cpu(cpu, cpu_mask))
		update_cpu_closid_rmid(r);
	smp_call_function_many(cpu_mask, update_cpu_closid_rmid, r, 1);
	put_cpu();
}