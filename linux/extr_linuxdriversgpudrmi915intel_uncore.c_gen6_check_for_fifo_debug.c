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
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int) ; 
 int /*<<< orphan*/  GTFIFODBG ; 
 int __raw_i915_read32 (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_i915_write32 (struct drm_i915_private*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool
gen6_check_for_fifo_debug(struct drm_i915_private *dev_priv)
{
	u32 fifodbg;

	fifodbg = __raw_i915_read32(dev_priv, GTFIFODBG);

	if (unlikely(fifodbg)) {
		DRM_DEBUG_DRIVER("GTFIFODBG = 0x08%x\n", fifodbg);
		__raw_i915_write32(dev_priv, GTFIFODBG, fifodbg);
	}

	return fifodbg;
}