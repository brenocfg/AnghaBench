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
struct drm_i915_private {int /*<<< orphan*/  pcu_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSP_MAXFIFO_PM5_ENABLE ; 
 int /*<<< orphan*/  PUNIT_REG_DSPFREQ ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlv_punit_read (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlv_punit_write (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void chv_set_memory_pm5(struct drm_i915_private *dev_priv, bool enable)
{
	u32 val;

	mutex_lock(&dev_priv->pcu_lock);

	val = vlv_punit_read(dev_priv, PUNIT_REG_DSPFREQ);
	if (enable)
		val |= DSP_MAXFIFO_PM5_ENABLE;
	else
		val &= ~DSP_MAXFIFO_PM5_ENABLE;
	vlv_punit_write(dev_priv, PUNIT_REG_DSPFREQ, val);

	mutex_unlock(&dev_priv->pcu_lock);
}