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
struct drm_i915_private {int dummy; } ;
typedef  enum skl_power_gate { ____Placeholder_skl_power_gate } skl_power_gate ;

/* Variables and functions */
 int /*<<< orphan*/  SKL_FUSE_PG_DIST_STATUS (int) ; 
 int /*<<< orphan*/  SKL_FUSE_STATUS ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_de_wait_for_set (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void gen9_wait_for_power_well_fuses(struct drm_i915_private *dev_priv,
					   enum skl_power_gate pg)
{
	/* Timeout 5us for PG#0, for other PGs 1us */
	WARN_ON(intel_de_wait_for_set(dev_priv, SKL_FUSE_STATUS,
				      SKL_FUSE_PG_DIST_STATUS(pg), 1));
}