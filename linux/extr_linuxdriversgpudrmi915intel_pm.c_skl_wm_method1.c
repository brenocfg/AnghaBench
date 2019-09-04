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
typedef  int /*<<< orphan*/  uint_fixed_16_16_t ;
typedef  int uint8_t ;
typedef  int uint32_t ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FP_16_16_MAX ; 
 int INTEL_GEN (struct drm_i915_private const*) ; 
 int /*<<< orphan*/  add_fixed16_u32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  div_fixed16 (int,int) ; 

__attribute__((used)) static uint_fixed_16_16_t
skl_wm_method1(const struct drm_i915_private *dev_priv, uint32_t pixel_rate,
	       uint8_t cpp, uint32_t latency, uint32_t dbuf_block_size)
{
	uint32_t wm_intermediate_val;
	uint_fixed_16_16_t ret;

	if (latency == 0)
		return FP_16_16_MAX;

	wm_intermediate_val = latency * pixel_rate * cpp;
	ret = div_fixed16(wm_intermediate_val, 1000 * dbuf_block_size);

	if (INTEL_GEN(dev_priv) >= 10)
		ret = add_fixed16_u32(ret, 1);

	return ret;
}