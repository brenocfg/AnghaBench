#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int physid; } ;
struct TYPE_5__ {TYPE_1__ cpu_info; } ;
typedef  TYPE_2__ klcpu_t ;
typedef  int /*<<< orphan*/  cpuid_t ;

/* Variables and functions */
 TYPE_2__* sn_get_cpuinfo (int /*<<< orphan*/ ) ; 

int get_cpu_slice(cpuid_t cpu)
{
	klcpu_t *acpu;

	if ((acpu = sn_get_cpuinfo(cpu)) == NULL)
		return -1;
	return acpu->cpu_info.physid;
}