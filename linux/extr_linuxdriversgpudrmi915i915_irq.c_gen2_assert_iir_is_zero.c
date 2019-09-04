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
typedef  scalar_t__ u16 ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 scalar_t__ I915_READ16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE16 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  POSTING_READ16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gen2_assert_iir_is_zero(struct drm_i915_private *dev_priv,
				    i915_reg_t reg)
{
	u16 val = I915_READ16(reg);

	if (val == 0)
		return;

	WARN(1, "Interrupt register 0x%x is not zero: 0x%08x\n",
	     i915_mmio_reg_offset(reg), val);
	I915_WRITE16(reg, 0xffff);
	POSTING_READ16(reg);
	I915_WRITE16(reg, 0xffff);
	POSTING_READ16(reg);
}