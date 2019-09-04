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
typedef  int u64 ;
struct cpuinfo_x86 {int dummy; } ;

/* Variables and functions */
 int ENERGY_PERF_BIAS_NORMAL ; 
 int ENERGY_PERF_BIAS_PERFORMANCE ; 
 int /*<<< orphan*/  MSR_IA32_ENERGY_PERF_BIAS ; 
 int /*<<< orphan*/  X86_FEATURE_EPB ; 
 int /*<<< orphan*/  cpu_has (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn_once (char*) ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_intel_energy_perf(struct cpuinfo_x86 *c)
{
	u64 epb;

	/*
	 * Initialize MSR_IA32_ENERGY_PERF_BIAS if not already initialized.
	 * (x86_energy_perf_policy(8) is available to change it at run-time.)
	 */
	if (!cpu_has(c, X86_FEATURE_EPB))
		return;

	rdmsrl(MSR_IA32_ENERGY_PERF_BIAS, epb);
	if ((epb & 0xF) != ENERGY_PERF_BIAS_PERFORMANCE)
		return;

	pr_warn_once("ENERGY_PERF_BIAS: Set to 'normal', was 'performance'\n");
	pr_warn_once("ENERGY_PERF_BIAS: View and update with x86_energy_perf_policy(8)\n");
	epb = (epb & ~0xF) | ENERGY_PERF_BIAS_NORMAL;
	wrmsrl(MSR_IA32_ENERGY_PERF_BIAS, epb);
}