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
typedef  scalar_t__ u32 ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
#define  EU_PERF_CNTL0 134 
#define  EU_PERF_CNTL1 133 
#define  EU_PERF_CNTL2 132 
#define  EU_PERF_CNTL3 131 
#define  EU_PERF_CNTL4 130 
#define  EU_PERF_CNTL5 129 
#define  EU_PERF_CNTL6 128 
 scalar_t__ i915_mmio_reg_offset (int /*<<< orphan*/  const) ; 

__attribute__((used)) static bool gen8_is_valid_flex_addr(struct drm_i915_private *dev_priv, u32 addr)
{
	static const i915_reg_t flex_eu_regs[] = {
		EU_PERF_CNTL0,
		EU_PERF_CNTL1,
		EU_PERF_CNTL2,
		EU_PERF_CNTL3,
		EU_PERF_CNTL4,
		EU_PERF_CNTL5,
		EU_PERF_CNTL6,
	};
	int i;

	for (i = 0; i < ARRAY_SIZE(flex_eu_regs); i++) {
		if (i915_mmio_reg_offset(flex_eu_regs[i]) == addr)
			return true;
	}
	return false;
}