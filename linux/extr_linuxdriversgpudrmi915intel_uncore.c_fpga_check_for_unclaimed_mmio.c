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

/* Variables and functions */
 int /*<<< orphan*/  FPGA_DBG ; 
 int FPGA_DBG_RM_NOCLAIM ; 
 int __raw_i915_read32 (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_i915_write32 (struct drm_i915_private*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static bool
fpga_check_for_unclaimed_mmio(struct drm_i915_private *dev_priv)
{
	u32 dbg;

	dbg = __raw_i915_read32(dev_priv, FPGA_DBG);
	if (likely(!(dbg & FPGA_DBG_RM_NOCLAIM)))
		return false;

	__raw_i915_write32(dev_priv, FPGA_DBG, FPGA_DBG_RM_NOCLAIM);

	return true;
}