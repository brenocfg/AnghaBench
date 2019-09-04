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
struct TYPE_2__ {int /*<<< orphan*/  conf; int /*<<< orphan*/  options_dyn; int /*<<< orphan*/  options; } ;
struct cpuinfo_mips {TYPE_1__ guest; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 unsigned int MIPS_CONF1_FP ; 
 unsigned int MIPS_CONF1_PC ; 
 unsigned int MIPS_CONF1_WR ; 
 unsigned int MIPS_CONF_M ; 
 int /*<<< orphan*/  MIPS_CPU_FPU ; 
 int /*<<< orphan*/  MIPS_CPU_PERF ; 
 int /*<<< orphan*/  MIPS_CPU_WATCH ; 
 int /*<<< orphan*/  probe_gc0_config_dyn (unsigned int,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static inline unsigned int decode_guest_config1(struct cpuinfo_mips *c)
{
	unsigned int config1, config1_dyn;

	probe_gc0_config_dyn(config1, config1, config1_dyn,
			     MIPS_CONF_M | MIPS_CONF1_PC | MIPS_CONF1_WR |
			     MIPS_CONF1_FP);

	if (config1 & MIPS_CONF1_FP)
		c->guest.options |= MIPS_CPU_FPU;
	if (config1_dyn & MIPS_CONF1_FP)
		c->guest.options_dyn |= MIPS_CPU_FPU;

	if (config1 & MIPS_CONF1_WR)
		c->guest.options |= MIPS_CPU_WATCH;
	if (config1_dyn & MIPS_CONF1_WR)
		c->guest.options_dyn |= MIPS_CPU_WATCH;

	if (config1 & MIPS_CONF1_PC)
		c->guest.options |= MIPS_CPU_PERF;
	if (config1_dyn & MIPS_CONF1_PC)
		c->guest.options_dyn |= MIPS_CPU_PERF;

	if (config1 & MIPS_CONF_M)
		c->guest.conf |= BIT(2);
	return config1 & MIPS_CONF_M;
}