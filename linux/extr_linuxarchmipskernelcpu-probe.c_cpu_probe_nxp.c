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
struct cpuinfo_mips {int processor_id; int /*<<< orphan*/  cputype; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_PR4450 ; 
 int /*<<< orphan*/  MIPS_CPU_ISA_M32R1 ; 
 int PRID_IMP_MASK ; 
#define  PRID_IMP_PR4450 128 
 char** __cpu_name ; 
 int /*<<< orphan*/  decode_configs (struct cpuinfo_mips*) ; 
 int /*<<< orphan*/  set_isa (struct cpuinfo_mips*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cpu_probe_nxp(struct cpuinfo_mips *c, unsigned int cpu)
{
	decode_configs(c);
	switch (c->processor_id & PRID_IMP_MASK) {
	case PRID_IMP_PR4450:
		c->cputype = CPU_PR4450;
		__cpu_name[cpu] = "Philips PR4450";
		set_isa(c, MIPS_CPU_ISA_M32R1);
		break;
	}
}