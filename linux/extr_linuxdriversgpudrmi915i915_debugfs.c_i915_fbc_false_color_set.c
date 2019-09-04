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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  lock; scalar_t__ false_color; } ;
struct drm_i915_private {TYPE_1__ fbc; } ;

/* Variables and functions */
 int ENODEV ; 
 int FBC_CTL_FALSE_COLOR ; 
 int /*<<< orphan*/  HAS_FBC (struct drm_i915_private*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ILK_DPFC_CONTROL ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i915_fbc_false_color_set(void *data, u64 val)
{
	struct drm_i915_private *dev_priv = data;
	u32 reg;

	if (INTEL_GEN(dev_priv) < 7 || !HAS_FBC(dev_priv))
		return -ENODEV;

	mutex_lock(&dev_priv->fbc.lock);

	reg = I915_READ(ILK_DPFC_CONTROL);
	dev_priv->fbc.false_color = val;

	I915_WRITE(ILK_DPFC_CONTROL, val ?
		   (reg | FBC_CTL_FALSE_COLOR) :
		   (reg & ~FBC_CTL_FALSE_COLOR));

	mutex_unlock(&dev_priv->fbc.lock);
	return 0;
}