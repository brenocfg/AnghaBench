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
typedef  int u64 ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct cpuinfo_mips {int options; TYPE_1__ scache; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int FTLB_EN ; 
 int FTLB_SET_PROB ; 
 int /*<<< orphan*/  MIPS_CACHE_NOT_PRESENT ; 
 int MIPS_CPU_4KEX ; 
 int MIPS_CPU_4K_CACHE ; 
 int MIPS_CPU_COUNTER ; 
 int MIPS_CPU_DIVEC ; 
 int MIPS_CPU_EBASE_WG ; 
 int MIPS_CPU_LLSC ; 
 int MIPS_CPU_MCHECK ; 
 int MIPS_EBASE_WG ; 
 unsigned int ST0_BEV ; 
 int /*<<< orphan*/  back_to_back_c0_hazard () ; 
 int /*<<< orphan*/  core_nvpes () ; 
 scalar_t__ cpu_has_mips64r6 ; 
 scalar_t__ cpu_has_mips_r2_r6 ; 
 scalar_t__ cpu_has_mipsmt ; 
 int /*<<< orphan*/  cpu_set_core (struct cpuinfo_mips*,unsigned int) ; 
 int decode_config0 (struct cpuinfo_mips*) ; 
 int decode_config1 (struct cpuinfo_mips*) ; 
 int decode_config2 (struct cpuinfo_mips*) ; 
 int decode_config3 (struct cpuinfo_mips*) ; 
 int decode_config4 (struct cpuinfo_mips*) ; 
 int decode_config5 (struct cpuinfo_mips*) ; 
 int fls (int /*<<< orphan*/ ) ; 
 unsigned int get_ebase_cpunum () ; 
 int /*<<< orphan*/  irq_enable_hazard () ; 
 scalar_t__ mips_ftlb_disabled ; 
 int /*<<< orphan*/  mips_probe_watch_registers (struct cpuinfo_mips*) ; 
 int read_c0_ebase () ; 
 int read_c0_ebase_64 () ; 
 unsigned int read_c0_status () ; 
 int /*<<< orphan*/  set_ftlb_enable (struct cpuinfo_mips*,int) ; 
 int /*<<< orphan*/  write_c0_ebase (int) ; 
 int /*<<< orphan*/  write_c0_ebase_64 (int) ; 
 int /*<<< orphan*/  write_c0_status (unsigned int) ; 

__attribute__((used)) static void decode_configs(struct cpuinfo_mips *c)
{
	int ok;

	/* MIPS32 or MIPS64 compliant CPU.  */
	c->options = MIPS_CPU_4KEX | MIPS_CPU_4K_CACHE | MIPS_CPU_COUNTER |
		     MIPS_CPU_DIVEC | MIPS_CPU_LLSC | MIPS_CPU_MCHECK;

	c->scache.flags = MIPS_CACHE_NOT_PRESENT;

	/* Enable FTLB if present and not disabled */
	set_ftlb_enable(c, mips_ftlb_disabled ? 0 : FTLB_EN);

	ok = decode_config0(c);			/* Read Config registers.  */
	BUG_ON(!ok);				/* Arch spec violation!	 */
	if (ok)
		ok = decode_config1(c);
	if (ok)
		ok = decode_config2(c);
	if (ok)
		ok = decode_config3(c);
	if (ok)
		ok = decode_config4(c);
	if (ok)
		ok = decode_config5(c);

	/* Probe the EBase.WG bit */
	if (cpu_has_mips_r2_r6) {
		u64 ebase;
		unsigned int status;

		/* {read,write}_c0_ebase_64() may be UNDEFINED prior to r6 */
		ebase = cpu_has_mips64r6 ? read_c0_ebase_64()
					 : (s32)read_c0_ebase();
		if (ebase & MIPS_EBASE_WG) {
			/* WG bit already set, we can avoid the clumsy probe */
			c->options |= MIPS_CPU_EBASE_WG;
		} else {
			/* Its UNDEFINED to change EBase while BEV=0 */
			status = read_c0_status();
			write_c0_status(status | ST0_BEV);
			irq_enable_hazard();
			/*
			 * On pre-r6 cores, this may well clobber the upper bits
			 * of EBase. This is hard to avoid without potentially
			 * hitting UNDEFINED dm*c0 behaviour if EBase is 32-bit.
			 */
			if (cpu_has_mips64r6)
				write_c0_ebase_64(ebase | MIPS_EBASE_WG);
			else
				write_c0_ebase(ebase | MIPS_EBASE_WG);
			back_to_back_c0_hazard();
			/* Restore BEV */
			write_c0_status(status);
			if (read_c0_ebase() & MIPS_EBASE_WG) {
				c->options |= MIPS_CPU_EBASE_WG;
				write_c0_ebase(ebase);
			}
		}
	}

	/* configure the FTLB write probability */
	set_ftlb_enable(c, (mips_ftlb_disabled ? 0 : FTLB_EN) | FTLB_SET_PROB);

	mips_probe_watch_registers(c);

#ifndef CONFIG_MIPS_CPS
	if (cpu_has_mips_r2_r6) {
		unsigned int core;

		core = get_ebase_cpunum();
		if (cpu_has_mipsmt)
			core >>= fls(core_nvpes()) - 1;
		cpu_set_core(c, core);
	}
#endif
}