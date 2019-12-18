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
struct drm_i915_private {int /*<<< orphan*/  sb_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIXCLK_GATE ; 
 int /*<<< orphan*/  PIXCLK_GATE_GATE ; 
 int /*<<< orphan*/  SBI_ICLK ; 
 int /*<<< orphan*/  SBI_SSCCTL6 ; 
 int /*<<< orphan*/  SBI_SSCCTL_DISABLE ; 
 int /*<<< orphan*/  intel_sbi_read (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_sbi_write (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void lpt_disable_iclkip(struct drm_i915_private *dev_priv)
{
	u32 temp;

	I915_WRITE(PIXCLK_GATE, PIXCLK_GATE_GATE);

	mutex_lock(&dev_priv->sb_lock);

	temp = intel_sbi_read(dev_priv, SBI_SSCCTL6, SBI_ICLK);
	temp |= SBI_SSCCTL_DISABLE;
	intel_sbi_write(dev_priv, SBI_SSCCTL6, temp, SBI_ICLK);

	mutex_unlock(&dev_priv->sb_lock);
}