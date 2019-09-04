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
 int /*<<< orphan*/  CPU_ALCHEMY ; 
#define  PRID_IMP_AU1_REV1 129 
#define  PRID_IMP_AU1_REV2 128 
 int PRID_IMP_MASK ; 
 int PRID_REV_MASK ; 
 char** __cpu_name ; 
 int /*<<< orphan*/  decode_configs (struct cpuinfo_mips*) ; 

__attribute__((used)) static inline void cpu_probe_alchemy(struct cpuinfo_mips *c, unsigned int cpu)
{
	decode_configs(c);
	switch (c->processor_id & PRID_IMP_MASK) {
	case PRID_IMP_AU1_REV1:
	case PRID_IMP_AU1_REV2:
		c->cputype = CPU_ALCHEMY;
		switch ((c->processor_id >> 24) & 0xff) {
		case 0:
			__cpu_name[cpu] = "Au1000";
			break;
		case 1:
			__cpu_name[cpu] = "Au1500";
			break;
		case 2:
			__cpu_name[cpu] = "Au1100";
			break;
		case 3:
			__cpu_name[cpu] = "Au1550";
			break;
		case 4:
			__cpu_name[cpu] = "Au1200";
			if ((c->processor_id & PRID_REV_MASK) == 2)
				__cpu_name[cpu] = "Au1250";
			break;
		case 5:
			__cpu_name[cpu] = "Au1210";
			break;
		default:
			__cpu_name[cpu] = "Au1xxx";
			break;
		}
		break;
	}
}