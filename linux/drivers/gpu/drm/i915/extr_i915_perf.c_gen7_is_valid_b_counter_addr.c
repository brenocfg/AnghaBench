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

/* Variables and functions */
 int /*<<< orphan*/  OACEC0_0 ; 
 int /*<<< orphan*/  OACEC7_1 ; 
 int /*<<< orphan*/  OAREPORTTRIG1 ; 
 int /*<<< orphan*/  OAREPORTTRIG8 ; 
 int /*<<< orphan*/  OASTARTTRIG1 ; 
 int /*<<< orphan*/  OASTARTTRIG8 ; 
 scalar_t__ i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool gen7_is_valid_b_counter_addr(struct drm_i915_private *dev_priv, u32 addr)
{
	return (addr >= i915_mmio_reg_offset(OASTARTTRIG1) &&
		addr <= i915_mmio_reg_offset(OASTARTTRIG8)) ||
		(addr >= i915_mmio_reg_offset(OAREPORTTRIG1) &&
		 addr <= i915_mmio_reg_offset(OAREPORTTRIG8)) ||
		(addr >= i915_mmio_reg_offset(OACEC0_0) &&
		 addr <= i915_mmio_reg_offset(OACEC7_1));
}