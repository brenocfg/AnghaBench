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
struct TYPE_2__ {int symmetric_memory; } ;
struct drm_i915_private {TYPE_1__ dram_info; } ;

/* Variables and functions */
 scalar_t__ IS_COFFEELAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_KABYLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_SKYLAKE (struct drm_i915_private*) ; 

__attribute__((used)) static bool intel_can_enable_ipc(struct drm_i915_private *dev_priv)
{
	/* Display WA #0477 WaDisableIPC: skl */
	if (IS_SKYLAKE(dev_priv))
		return false;

	/* Display WA #1141: SKL:all KBL:all CFL */
	if (IS_KABYLAKE(dev_priv) || IS_COFFEELAKE(dev_priv))
		return dev_priv->dram_info.symmetric_memory;

	return true;
}