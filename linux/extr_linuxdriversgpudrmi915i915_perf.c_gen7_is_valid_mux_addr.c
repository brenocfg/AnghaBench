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
 int /*<<< orphan*/  HALF_SLICE_CHICKEN2 ; 
 int /*<<< orphan*/  MICRO_BP0_0 ; 
 int /*<<< orphan*/  NOA_WRITE ; 
 int /*<<< orphan*/  OA_PERFCNT1_LO ; 
 int /*<<< orphan*/  OA_PERFCNT2_HI ; 
 int /*<<< orphan*/  OA_PERFMATRIX_HI ; 
 int /*<<< orphan*/  OA_PERFMATRIX_LO ; 
 scalar_t__ i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool gen7_is_valid_mux_addr(struct drm_i915_private *dev_priv, u32 addr)
{
	return addr == i915_mmio_reg_offset(HALF_SLICE_CHICKEN2) ||
		(addr >= i915_mmio_reg_offset(MICRO_BP0_0) &&
		 addr <= i915_mmio_reg_offset(NOA_WRITE)) ||
		(addr >= i915_mmio_reg_offset(OA_PERFCNT1_LO) &&
		 addr <= i915_mmio_reg_offset(OA_PERFCNT2_HI)) ||
		(addr >= i915_mmio_reg_offset(OA_PERFMATRIX_LO) &&
		 addr <= i915_mmio_reg_offset(OA_PERFMATRIX_HI));
}