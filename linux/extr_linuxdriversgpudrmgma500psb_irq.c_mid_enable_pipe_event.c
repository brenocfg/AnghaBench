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
struct drm_psb_private {int /*<<< orphan*/  dev; int /*<<< orphan*/  vdc_irq_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSB_INT_ENABLE_R ; 
 int /*<<< orphan*/  PSB_INT_MASK_R ; 
 int /*<<< orphan*/  PSB_WVDC32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gma_power_begin (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gma_power_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mid_pipe_event (int) ; 

__attribute__((used)) static void mid_enable_pipe_event(struct drm_psb_private *dev_priv, int pipe)
{
	if (gma_power_begin(dev_priv->dev, false)) {
		u32 pipe_event = mid_pipe_event(pipe);
		dev_priv->vdc_irq_mask |= pipe_event;
		PSB_WVDC32(~dev_priv->vdc_irq_mask, PSB_INT_MASK_R);
		PSB_WVDC32(dev_priv->vdc_irq_mask, PSB_INT_ENABLE_R);
		gma_power_end(dev_priv->dev);
	}
}