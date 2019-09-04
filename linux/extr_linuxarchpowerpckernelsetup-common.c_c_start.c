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
struct seq_file {int dummy; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_online_mask ; 
 scalar_t__ cpumask_first (int /*<<< orphan*/ ) ; 
 scalar_t__ cpumask_next (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ nr_cpu_ids ; 

__attribute__((used)) static void *c_start(struct seq_file *m, loff_t *pos)
{
	if (*pos == 0)	/* just in case, cpu 0 is not the first */
		*pos = cpumask_first(cpu_online_mask);
	else
		*pos = cpumask_next(*pos - 1, cpu_online_mask);
	if ((*pos) < nr_cpu_ids)
		return (void *)(unsigned long)(*pos + 1);
	return NULL;
}