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
struct pps_registers {int /*<<< orphan*/  pp_stat; } ;
struct intel_dp {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int /*<<< orphan*/  intel_pps_get_registers (struct intel_dp*,struct pps_registers*) ; 

__attribute__((used)) static i915_reg_t
_pp_stat_reg(struct intel_dp *intel_dp)
{
	struct pps_registers regs;

	intel_pps_get_registers(intel_dp, &regs);

	return regs.pp_stat;
}