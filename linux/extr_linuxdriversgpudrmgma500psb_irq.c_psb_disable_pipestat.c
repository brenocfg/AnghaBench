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
struct drm_psb_private {int* pipestat; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int PSB_RVDC32 (int) ; 
 int /*<<< orphan*/  PSB_WVDC32 (int,int) ; 
 scalar_t__ gma_power_begin (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gma_power_end (int /*<<< orphan*/ ) ; 
 int psb_pipestat (int) ; 

void
psb_disable_pipestat(struct drm_psb_private *dev_priv, int pipe, u32 mask)
{
	if ((dev_priv->pipestat[pipe] & mask) != 0) {
		u32 reg = psb_pipestat(pipe);
		dev_priv->pipestat[pipe] &= ~mask;
		if (gma_power_begin(dev_priv->dev, false)) {
			u32 writeVal = PSB_RVDC32(reg);
			writeVal &= ~mask;
			PSB_WVDC32(writeVal, reg);
			(void) PSB_RVDC32(reg);
			gma_power_end(dev_priv->dev);
		}
	}
}