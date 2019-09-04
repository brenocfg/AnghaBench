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
struct cpuinfo_mips {int options; } ;

/* Variables and functions */
 unsigned int MIPS_CONF_AR ; 
 unsigned int MIPS_CONF_AT ; 
 unsigned int MIPS_CONF_M ; 
 unsigned int MIPS_CONF_MT ; 
 int MIPS_CONF_MT_FTLB ; 
 int MIPS_CONF_MT_TLB ; 
 int MIPS_CPU_FTLB ; 
 int /*<<< orphan*/  MIPS_CPU_ISA_M32R1 ; 
 int /*<<< orphan*/  MIPS_CPU_ISA_M32R2 ; 
 int /*<<< orphan*/  MIPS_CPU_ISA_M32R6 ; 
 int /*<<< orphan*/  MIPS_CPU_ISA_M64R1 ; 
 int /*<<< orphan*/  MIPS_CPU_ISA_M64R2 ; 
 int /*<<< orphan*/  MIPS_CPU_ISA_M64R6 ; 
 int MIPS_CPU_TLB ; 
 int /*<<< orphan*/  panic (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int read_c0_config () ; 
 int /*<<< orphan*/  set_isa (struct cpuinfo_mips*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unknown_isa ; 

__attribute__((used)) static inline unsigned int decode_config0(struct cpuinfo_mips *c)
{
	unsigned int config0;
	int isa, mt;

	config0 = read_c0_config();

	/*
	 * Look for Standard TLB or Dual VTLB and FTLB
	 */
	mt = config0 & MIPS_CONF_MT;
	if (mt == MIPS_CONF_MT_TLB)
		c->options |= MIPS_CPU_TLB;
	else if (mt == MIPS_CONF_MT_FTLB)
		c->options |= MIPS_CPU_TLB | MIPS_CPU_FTLB;

	isa = (config0 & MIPS_CONF_AT) >> 13;
	switch (isa) {
	case 0:
		switch ((config0 & MIPS_CONF_AR) >> 10) {
		case 0:
			set_isa(c, MIPS_CPU_ISA_M32R1);
			break;
		case 1:
			set_isa(c, MIPS_CPU_ISA_M32R2);
			break;
		case 2:
			set_isa(c, MIPS_CPU_ISA_M32R6);
			break;
		default:
			goto unknown;
		}
		break;
	case 2:
		switch ((config0 & MIPS_CONF_AR) >> 10) {
		case 0:
			set_isa(c, MIPS_CPU_ISA_M64R1);
			break;
		case 1:
			set_isa(c, MIPS_CPU_ISA_M64R2);
			break;
		case 2:
			set_isa(c, MIPS_CPU_ISA_M64R6);
			break;
		default:
			goto unknown;
		}
		break;
	default:
		goto unknown;
	}

	return config0 & MIPS_CONF_M;

unknown:
	panic(unknown_isa, config0);
}