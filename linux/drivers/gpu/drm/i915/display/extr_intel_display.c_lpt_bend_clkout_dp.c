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
struct drm_i915_private {int /*<<< orphan*/  sb_lock; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int BEND_IDX (int) ; 
 int /*<<< orphan*/  SBI_ICLK ; 
 int /*<<< orphan*/  SBI_SSCDITHPHASE ; 
 int /*<<< orphan*/  SBI_SSCDIVINTPHASE ; 
 scalar_t__ WARN_ON (int) ; 
 int intel_sbi_read (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_sbi_write (struct drm_i915_private*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int* sscdivintphase ; 

__attribute__((used)) static void lpt_bend_clkout_dp(struct drm_i915_private *dev_priv, int steps)
{
	u32 tmp;
	int idx = BEND_IDX(steps);

	if (WARN_ON(steps % 5 != 0))
		return;

	if (WARN_ON(idx >= ARRAY_SIZE(sscdivintphase)))
		return;

	mutex_lock(&dev_priv->sb_lock);

	if (steps % 10 != 0)
		tmp = 0xAAAAAAAB;
	else
		tmp = 0x00000000;
	intel_sbi_write(dev_priv, SBI_SSCDITHPHASE, tmp, SBI_ICLK);

	tmp = intel_sbi_read(dev_priv, SBI_SSCDIVINTPHASE, SBI_ICLK);
	tmp &= 0xffff0000;
	tmp |= sscdivintphase[idx];
	intel_sbi_write(dev_priv, SBI_SSCDIVINTPHASE, tmp, SBI_ICLK);

	mutex_unlock(&dev_priv->sb_lock);
}