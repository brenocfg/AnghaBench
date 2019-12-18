#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct drm_i915_private {int edram_size_mb; TYPE_1__ drm; int /*<<< orphan*/  uncore; } ;

/* Variables and functions */
 int EDRAM_ENABLED ; 
 int /*<<< orphan*/  HSW_EDRAM_CAP ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 int __raw_uncore_read32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int gen9_edram_size_mb (struct drm_i915_private*,int) ; 

__attribute__((used)) static void edram_detect(struct drm_i915_private *dev_priv)
{
	u32 edram_cap = 0;

	if (!(IS_HASWELL(dev_priv) ||
	      IS_BROADWELL(dev_priv) ||
	      INTEL_GEN(dev_priv) >= 9))
		return;

	edram_cap = __raw_uncore_read32(&dev_priv->uncore, HSW_EDRAM_CAP);

	/* NB: We can't write IDICR yet because we don't have gt funcs set up */

	if (!(edram_cap & EDRAM_ENABLED))
		return;

	/*
	 * The needed capability bits for size calculation are not there with
	 * pre gen9 so return 128MB always.
	 */
	if (INTEL_GEN(dev_priv) < 9)
		dev_priv->edram_size_mb = 128;
	else
		dev_priv->edram_size_mb =
			gen9_edram_size_mb(dev_priv, edram_cap);

	dev_info(dev_priv->drm.dev,
		 "Found %uMB of eDRAM\n", dev_priv->edram_size_mb);
}