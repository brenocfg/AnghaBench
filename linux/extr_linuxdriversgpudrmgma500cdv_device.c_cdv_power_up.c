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
struct drm_psb_private {scalar_t__ apm_base; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 scalar_t__ PSB_APM_CMD ; 
 scalar_t__ PSB_APM_STS ; 
 int PSB_PWRGT_GFX_D0 ; 
 int PSB_PWRGT_GFX_MASK ; 
 int PSB_PWRGT_GFX_ON ; 
 int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int cdv_power_up(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	u32 pwr_cnt, pwr_mask, pwr_sts;
	int tries = 5;

	pwr_cnt = inl(dev_priv->apm_base + PSB_APM_CMD);
	pwr_cnt &= ~PSB_PWRGT_GFX_MASK;
	pwr_cnt |= PSB_PWRGT_GFX_ON;
	pwr_mask = PSB_PWRGT_GFX_MASK;

	outl(pwr_cnt, dev_priv->apm_base + PSB_APM_CMD);

	while (tries--) {
		pwr_sts = inl(dev_priv->apm_base + PSB_APM_STS);
		if ((pwr_sts & pwr_mask) == PSB_PWRGT_GFX_D0)
			return 0;
		udelay(10);
	}
	return 0;
}