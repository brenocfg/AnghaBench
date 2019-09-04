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
struct cpuinfo_mips {int /*<<< orphan*/  ases; int /*<<< orphan*/  options; } ;

/* Variables and functions */
 int /*<<< orphan*/  HWCAP_MIPS_CRC32 ; 
 int /*<<< orphan*/  MIPS_ASE_MIPS16E2 ; 
 unsigned int MIPS_CONF5_CA2 ; 
 unsigned int MIPS_CONF5_CRCP ; 
 unsigned int MIPS_CONF5_EVA ; 
 unsigned int MIPS_CONF5_LLB ; 
 unsigned int MIPS_CONF5_MRP ; 
 unsigned int MIPS_CONF5_MVH ; 
 unsigned int MIPS_CONF5_UFE ; 
 unsigned int MIPS_CONF5_UFR ; 
 unsigned int MIPS_CONF5_VP ; 
 unsigned int MIPS_CONF_M ; 
 int /*<<< orphan*/  MIPS_CPU_EVA ; 
 int /*<<< orphan*/  MIPS_CPU_MAAR ; 
 int /*<<< orphan*/  MIPS_CPU_MVH ; 
 int /*<<< orphan*/  MIPS_CPU_RW_LLB ; 
 int /*<<< orphan*/  MIPS_CPU_VP ; 
 scalar_t__ cpu_has_mips_r6 ; 
 int /*<<< orphan*/  elf_hwcap ; 
 unsigned int read_c0_config5 () ; 
 int /*<<< orphan*/  write_c0_config5 (unsigned int) ; 

__attribute__((used)) static inline unsigned int decode_config5(struct cpuinfo_mips *c)
{
	unsigned int config5;

	config5 = read_c0_config5();
	config5 &= ~(MIPS_CONF5_UFR | MIPS_CONF5_UFE);
	write_c0_config5(config5);

	if (config5 & MIPS_CONF5_EVA)
		c->options |= MIPS_CPU_EVA;
	if (config5 & MIPS_CONF5_MRP)
		c->options |= MIPS_CPU_MAAR;
	if (config5 & MIPS_CONF5_LLB)
		c->options |= MIPS_CPU_RW_LLB;
	if (config5 & MIPS_CONF5_MVH)
		c->options |= MIPS_CPU_MVH;
	if (cpu_has_mips_r6 && (config5 & MIPS_CONF5_VP))
		c->options |= MIPS_CPU_VP;
	if (config5 & MIPS_CONF5_CA2)
		c->ases |= MIPS_ASE_MIPS16E2;

	if (config5 & MIPS_CONF5_CRCP)
		elf_hwcap |= HWCAP_MIPS_CRC32;

	return config5 & MIPS_CONF_M;
}