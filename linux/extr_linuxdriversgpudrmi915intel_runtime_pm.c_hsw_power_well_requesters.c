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
typedef  enum i915_power_well_id { ____Placeholder_i915_power_well_id } i915_power_well_id ;

/* Variables and functions */
 int /*<<< orphan*/  HSW_PWR_WELL_CTL_BIOS (int) ; 
 int /*<<< orphan*/  HSW_PWR_WELL_CTL_DEBUG (int) ; 
 int /*<<< orphan*/  HSW_PWR_WELL_CTL_DRIVER (int) ; 
 int /*<<< orphan*/  HSW_PWR_WELL_CTL_KVMR ; 
 int HSW_PWR_WELL_CTL_REQ (int) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 hsw_power_well_requesters(struct drm_i915_private *dev_priv,
				     enum i915_power_well_id id)
{
	u32 req_mask = HSW_PWR_WELL_CTL_REQ(id);
	u32 ret;

	ret = I915_READ(HSW_PWR_WELL_CTL_BIOS(id)) & req_mask ? 1 : 0;
	ret |= I915_READ(HSW_PWR_WELL_CTL_DRIVER(id)) & req_mask ? 2 : 0;
	ret |= I915_READ(HSW_PWR_WELL_CTL_KVMR) & req_mask ? 4 : 0;
	ret |= I915_READ(HSW_PWR_WELL_CTL_DEBUG(id)) & req_mask ? 8 : 0;

	return ret;
}