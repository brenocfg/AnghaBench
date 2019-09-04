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
struct cpuinfo_mips {int /*<<< orphan*/  fpu_msk31; int /*<<< orphan*/  options; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPS_CPU_FPU ; 
 int /*<<< orphan*/  cpu_set_nan_2008 (struct cpuinfo_mips*) ; 
 int /*<<< orphan*/  cpu_set_nofpu_2008 (struct cpuinfo_mips*) ; 
 int /*<<< orphan*/  cpu_set_nofpu_id (struct cpuinfo_mips*) ; 
 int /*<<< orphan*/  mips_nofpu_msk31 ; 

__attribute__((used)) static void cpu_set_nofpu_opts(struct cpuinfo_mips *c)
{
	c->options &= ~MIPS_CPU_FPU;
	c->fpu_msk31 = mips_nofpu_msk31;

	cpu_set_nofpu_2008(c);
	cpu_set_nan_2008(c);
	cpu_set_nofpu_id(c);
}