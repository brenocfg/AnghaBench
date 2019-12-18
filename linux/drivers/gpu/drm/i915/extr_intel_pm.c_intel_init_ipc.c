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
struct drm_i915_private {int /*<<< orphan*/  ipc_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  HAS_IPC (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_can_enable_ipc (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_enable_ipc (struct drm_i915_private*) ; 

void intel_init_ipc(struct drm_i915_private *dev_priv)
{
	if (!HAS_IPC(dev_priv))
		return;

	dev_priv->ipc_enabled = intel_can_enable_ipc(dev_priv);

	intel_enable_ipc(dev_priv);
}