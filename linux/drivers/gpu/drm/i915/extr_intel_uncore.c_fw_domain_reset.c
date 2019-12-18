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
struct intel_uncore_forcewake_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fw_clear (struct intel_uncore_forcewake_domain const*,int) ; 

__attribute__((used)) static inline void
fw_domain_reset(const struct intel_uncore_forcewake_domain *d)
{
	/*
	 * We don't really know if the powerwell for the forcewake domain we are
	 * trying to reset here does exist at this point (engines could be fused
	 * off in ICL+), so no waiting for acks
	 */
	/* WaRsClearFWBitsAtReset:bdw,skl */
	fw_clear(d, 0xffff);
}