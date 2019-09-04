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
struct cpuinfo_mips {int processor_id; scalar_t__ cputype; int options; int tlbsize; int kscratch_mask; } ;

/* Variables and functions */
 scalar_t__ CPU_ALCHEMY ; 
 scalar_t__ CPU_XLP ; 
 void* CPU_XLR ; 
 int MIPS_CPU_4KEX ; 
 int MIPS_CPU_COUNTER ; 
 int MIPS_CPU_DIVEC ; 
 int MIPS_CPU_EJTAG ; 
 int MIPS_CPU_FPU ; 
 int /*<<< orphan*/  MIPS_CPU_ISA_M64R1 ; 
 int /*<<< orphan*/  MIPS_CPU_ISA_M64R2 ; 
 int MIPS_CPU_LLSC ; 
 int MIPS_CPU_MCHECK ; 
 int MIPS_CPU_TLB ; 
 int MIPS_CPU_ULRI ; 
 int MIPS_CPU_WATCH ; 
 int PRID_IMP_MASK ; 
 int PRID_IMP_NETLOGIC_AU13XX ; 
#define  PRID_IMP_NETLOGIC_XLP2XX 153 
#define  PRID_IMP_NETLOGIC_XLP3XX 152 
#define  PRID_IMP_NETLOGIC_XLP5XX 151 
#define  PRID_IMP_NETLOGIC_XLP8XX 150 
#define  PRID_IMP_NETLOGIC_XLP9XX 149 
#define  PRID_IMP_NETLOGIC_XLR308 148 
#define  PRID_IMP_NETLOGIC_XLR308C 147 
#define  PRID_IMP_NETLOGIC_XLR508C 146 
#define  PRID_IMP_NETLOGIC_XLR516C 145 
#define  PRID_IMP_NETLOGIC_XLR532 144 
#define  PRID_IMP_NETLOGIC_XLR532C 143 
#define  PRID_IMP_NETLOGIC_XLR716 142 
#define  PRID_IMP_NETLOGIC_XLR732 141 
#define  PRID_IMP_NETLOGIC_XLS104 140 
#define  PRID_IMP_NETLOGIC_XLS108 139 
#define  PRID_IMP_NETLOGIC_XLS204 138 
#define  PRID_IMP_NETLOGIC_XLS208 137 
#define  PRID_IMP_NETLOGIC_XLS404 136 
#define  PRID_IMP_NETLOGIC_XLS404B 135 
#define  PRID_IMP_NETLOGIC_XLS408 134 
#define  PRID_IMP_NETLOGIC_XLS408B 133 
#define  PRID_IMP_NETLOGIC_XLS412B 132 
#define  PRID_IMP_NETLOGIC_XLS416B 131 
#define  PRID_IMP_NETLOGIC_XLS608 130 
#define  PRID_IMP_NETLOGIC_XLS608B 129 
#define  PRID_IMP_NETLOGIC_XLS616B 128 
 char** __cpu_name ; 
 int /*<<< orphan*/  decode_configs (struct cpuinfo_mips*) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int read_c0_config1 () ; 
 int read_c0_config6 () ; 
 int /*<<< orphan*/  set_isa (struct cpuinfo_mips*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cpu_probe_netlogic(struct cpuinfo_mips *c, int cpu)
{
	decode_configs(c);

	if ((c->processor_id & PRID_IMP_MASK) == PRID_IMP_NETLOGIC_AU13XX) {
		c->cputype = CPU_ALCHEMY;
		__cpu_name[cpu] = "Au1300";
		/* following stuff is not for Alchemy */
		return;
	}

	c->options = (MIPS_CPU_TLB	 |
			MIPS_CPU_4KEX	 |
			MIPS_CPU_COUNTER |
			MIPS_CPU_DIVEC	 |
			MIPS_CPU_WATCH	 |
			MIPS_CPU_EJTAG	 |
			MIPS_CPU_LLSC);

	switch (c->processor_id & PRID_IMP_MASK) {
	case PRID_IMP_NETLOGIC_XLP2XX:
	case PRID_IMP_NETLOGIC_XLP9XX:
	case PRID_IMP_NETLOGIC_XLP5XX:
		c->cputype = CPU_XLP;
		__cpu_name[cpu] = "Broadcom XLPII";
		break;

	case PRID_IMP_NETLOGIC_XLP8XX:
	case PRID_IMP_NETLOGIC_XLP3XX:
		c->cputype = CPU_XLP;
		__cpu_name[cpu] = "Netlogic XLP";
		break;

	case PRID_IMP_NETLOGIC_XLR732:
	case PRID_IMP_NETLOGIC_XLR716:
	case PRID_IMP_NETLOGIC_XLR532:
	case PRID_IMP_NETLOGIC_XLR308:
	case PRID_IMP_NETLOGIC_XLR532C:
	case PRID_IMP_NETLOGIC_XLR516C:
	case PRID_IMP_NETLOGIC_XLR508C:
	case PRID_IMP_NETLOGIC_XLR308C:
		c->cputype = CPU_XLR;
		__cpu_name[cpu] = "Netlogic XLR";
		break;

	case PRID_IMP_NETLOGIC_XLS608:
	case PRID_IMP_NETLOGIC_XLS408:
	case PRID_IMP_NETLOGIC_XLS404:
	case PRID_IMP_NETLOGIC_XLS208:
	case PRID_IMP_NETLOGIC_XLS204:
	case PRID_IMP_NETLOGIC_XLS108:
	case PRID_IMP_NETLOGIC_XLS104:
	case PRID_IMP_NETLOGIC_XLS616B:
	case PRID_IMP_NETLOGIC_XLS608B:
	case PRID_IMP_NETLOGIC_XLS416B:
	case PRID_IMP_NETLOGIC_XLS412B:
	case PRID_IMP_NETLOGIC_XLS408B:
	case PRID_IMP_NETLOGIC_XLS404B:
		c->cputype = CPU_XLR;
		__cpu_name[cpu] = "Netlogic XLS";
		break;

	default:
		pr_info("Unknown Netlogic chip id [%02x]!\n",
		       c->processor_id);
		c->cputype = CPU_XLR;
		break;
	}

	if (c->cputype == CPU_XLP) {
		set_isa(c, MIPS_CPU_ISA_M64R2);
		c->options |= (MIPS_CPU_FPU | MIPS_CPU_ULRI | MIPS_CPU_MCHECK);
		/* This will be updated again after all threads are woken up */
		c->tlbsize = ((read_c0_config6() >> 16) & 0xffff) + 1;
	} else {
		set_isa(c, MIPS_CPU_ISA_M64R1);
		c->tlbsize = ((read_c0_config1() >> 25) & 0x3f) + 1;
	}
	c->kscratch_mask = 0xf;
}