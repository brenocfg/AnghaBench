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
struct skl_ddb_allocation {int /*<<< orphan*/  enabled_slices; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_enabled_dbuf_slices_num (struct drm_i915_private*) ; 

void skl_ddb_get_hw_state(struct drm_i915_private *dev_priv,
			  struct skl_ddb_allocation *ddb /* out */)
{
	ddb->enabled_slices = intel_enabled_dbuf_slices_num(dev_priv);
}