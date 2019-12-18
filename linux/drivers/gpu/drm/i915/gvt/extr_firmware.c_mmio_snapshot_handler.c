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
struct intel_gvt {struct drm_i915_private* dev_priv; } ;
struct drm_i915_private {int /*<<< orphan*/  uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  _MMIO (int) ; 
 int intel_uncore_read_notrace (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mmio_snapshot_handler(struct intel_gvt *gvt, u32 offset, void *data)
{
	struct drm_i915_private *i915 = gvt->dev_priv;

	*(u32 *)(data + offset) = intel_uncore_read_notrace(&i915->uncore,
							    _MMIO(offset));
	return 0;
}