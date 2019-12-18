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
typedef  int /*<<< orphan*/  u32 ;
struct drm_i915_private {scalar_t__ ipc_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISP_ARB_CTL2 ; 
 int /*<<< orphan*/  DISP_IPC_ENABLE ; 
 int /*<<< orphan*/  HAS_IPC (struct drm_i915_private*) ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void intel_enable_ipc(struct drm_i915_private *dev_priv)
{
	u32 val;

	if (!HAS_IPC(dev_priv))
		return;

	val = I915_READ(DISP_ARB_CTL2);

	if (dev_priv->ipc_enabled)
		val |= DISP_IPC_ENABLE;
	else
		val &= ~DISP_IPC_ENABLE;

	I915_WRITE(DISP_ARB_CTL2, val);
}