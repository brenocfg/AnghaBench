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
struct sh_cpuinfo {int /*<<< orphan*/  loops_per_jiffy; } ;

/* Variables and functions */
 int /*<<< orphan*/  boot_cpu_data ; 
 struct sh_cpuinfo* cpu_data ; 
 int /*<<< orphan*/  loops_per_jiffy ; 
 int /*<<< orphan*/  memcpy (struct sh_cpuinfo*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void smp_store_cpu_info(unsigned int cpu)
{
	struct sh_cpuinfo *c = cpu_data + cpu;

	memcpy(c, &boot_cpu_data, sizeof(struct sh_cpuinfo));

	c->loops_per_jiffy = loops_per_jiffy;
}