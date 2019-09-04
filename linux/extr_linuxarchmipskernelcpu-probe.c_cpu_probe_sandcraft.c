#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int ways; } ;
struct cpuinfo_mips {int processor_id; int tlbsize; TYPE_1__ scache; int /*<<< orphan*/  cputype; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SR71000 ; 
 int PRID_IMP_MASK ; 
#define  PRID_IMP_SR71000 128 
 char** __cpu_name ; 
 int /*<<< orphan*/  decode_configs (struct cpuinfo_mips*) ; 

__attribute__((used)) static inline void cpu_probe_sandcraft(struct cpuinfo_mips *c, unsigned int cpu)
{
	decode_configs(c);
	switch (c->processor_id & PRID_IMP_MASK) {
	case PRID_IMP_SR71000:
		c->cputype = CPU_SR71000;
		__cpu_name[cpu] = "Sandcraft SR71000";
		c->scache.ways = 8;
		c->tlbsize = 64;
		break;
	}
}