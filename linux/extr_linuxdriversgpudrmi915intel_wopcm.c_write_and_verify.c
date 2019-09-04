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
typedef  int u32 ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int write_and_verify(struct drm_i915_private *dev_priv,
				   i915_reg_t reg, u32 val, u32 mask,
				   u32 locked_bit)
{
	u32 reg_val;

	GEM_BUG_ON(val & ~mask);

	I915_WRITE(reg, val);

	reg_val = I915_READ(reg);

	return (reg_val & mask) != (val | locked_bit) ? -EIO : 0;
}