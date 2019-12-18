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
 scalar_t__ HAS_PCH_LPT_LP (struct drm_i915_private*) ; 
 int /*<<< orphan*/  SBI_DBUFF0 ; 
 int /*<<< orphan*/  SBI_GEN0 ; 
 int /*<<< orphan*/  SBI_GEN0_CFG_BUFFENABLE_DISABLE ; 
 int /*<<< orphan*/  SBI_ICLK ; 
 int /*<<< orphan*/  SBI_SSCCTL ; 
 int /*<<< orphan*/  SBI_SSCCTL_DISABLE ; 
 int /*<<< orphan*/  SBI_SSCCTL_PATHALT ; 
 scalar_t__ WARN (int,char*) ; 
 int /*<<< orphan*/  intel_sbi_read (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_sbi_write (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpt_program_fdi_mphy (struct drm_i915_private*) ; 
 int /*<<< orphan*/  lpt_reset_fdi_mphy (struct drm_i915_private*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void lpt_enable_clkout_dp(struct drm_i915_private *dev_priv,
				 bool with_spread, bool with_fdi)
{
	u32 reg, tmp;

	if (WARN(with_fdi && !with_spread, "FDI requires downspread\n"))
		with_spread = true;
	if (WARN(HAS_PCH_LPT_LP(dev_priv) &&
	    with_fdi, "LP PCH doesn't have FDI\n"))
		with_fdi = false;

	mutex_lock(&dev_priv->sb_lock);

	tmp = intel_sbi_read(dev_priv, SBI_SSCCTL, SBI_ICLK);
	tmp &= ~SBI_SSCCTL_DISABLE;
	tmp |= SBI_SSCCTL_PATHALT;
	intel_sbi_write(dev_priv, SBI_SSCCTL, tmp, SBI_ICLK);

	udelay(24);

	if (with_spread) {
		tmp = intel_sbi_read(dev_priv, SBI_SSCCTL, SBI_ICLK);
		tmp &= ~SBI_SSCCTL_PATHALT;
		intel_sbi_write(dev_priv, SBI_SSCCTL, tmp, SBI_ICLK);

		if (with_fdi) {
			lpt_reset_fdi_mphy(dev_priv);
			lpt_program_fdi_mphy(dev_priv);
		}
	}

	reg = HAS_PCH_LPT_LP(dev_priv) ? SBI_GEN0 : SBI_DBUFF0;
	tmp = intel_sbi_read(dev_priv, reg, SBI_ICLK);
	tmp |= SBI_GEN0_CFG_BUFFENABLE_DISABLE;
	intel_sbi_write(dev_priv, reg, tmp, SBI_ICLK);

	mutex_unlock(&dev_priv->sb_lock);
}