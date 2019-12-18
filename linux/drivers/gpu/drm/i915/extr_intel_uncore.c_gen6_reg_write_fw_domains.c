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
struct intel_uncore {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;
typedef  enum forcewake_domains { ____Placeholder_forcewake_domains } forcewake_domains ;

/* Variables and functions */
 int FORCEWAKE_RENDER ; 

__attribute__((used)) static enum forcewake_domains
gen6_reg_write_fw_domains(struct intel_uncore *uncore, i915_reg_t reg)
{
	return FORCEWAKE_RENDER;
}