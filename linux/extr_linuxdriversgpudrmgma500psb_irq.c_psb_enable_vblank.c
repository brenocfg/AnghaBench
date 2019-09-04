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
typedef  int uint32_t ;
struct drm_psb_private {int /*<<< orphan*/  irqmask_lock; int /*<<< orphan*/  vdc_irq_mask; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_MFLD (struct drm_device*) ; 
 int PIPEACONF_ENABLE ; 
 int /*<<< orphan*/  PIPE_VBLANK_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  PSB_INT_ENABLE_R ; 
 int /*<<< orphan*/  PSB_INT_MASK_R ; 
 int /*<<< orphan*/  PSB_WVDC32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REG_READ (int) ; 
 int /*<<< orphan*/  _PSB_VSYNC_PIPEA_FLAG ; 
 int /*<<< orphan*/  _PSB_VSYNC_PIPEB_FLAG ; 
 scalar_t__ gma_power_begin (struct drm_device*,int) ; 
 int /*<<< orphan*/  gma_power_end (struct drm_device*) ; 
 int mdfld_enable_te (struct drm_device*,unsigned int) ; 
 int mid_pipeconf (unsigned int) ; 
 int /*<<< orphan*/  psb_enable_pipestat (struct drm_psb_private*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int psb_enable_vblank(struct drm_device *dev, unsigned int pipe)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	unsigned long irqflags;
	uint32_t reg_val = 0;
	uint32_t pipeconf_reg = mid_pipeconf(pipe);

	/* Medfield is different - we should perhaps extract out vblank
	   and blacklight etc ops */
	if (IS_MFLD(dev))
		return mdfld_enable_te(dev, pipe);

	if (gma_power_begin(dev, false)) {
		reg_val = REG_READ(pipeconf_reg);
		gma_power_end(dev);
	}

	if (!(reg_val & PIPEACONF_ENABLE))
		return -EINVAL;

	spin_lock_irqsave(&dev_priv->irqmask_lock, irqflags);

	if (pipe == 0)
		dev_priv->vdc_irq_mask |= _PSB_VSYNC_PIPEA_FLAG;
	else if (pipe == 1)
		dev_priv->vdc_irq_mask |= _PSB_VSYNC_PIPEB_FLAG;

	PSB_WVDC32(~dev_priv->vdc_irq_mask, PSB_INT_MASK_R);
	PSB_WVDC32(dev_priv->vdc_irq_mask, PSB_INT_ENABLE_R);
	psb_enable_pipestat(dev_priv, pipe, PIPE_VBLANK_INTERRUPT_ENABLE);

	spin_unlock_irqrestore(&dev_priv->irqmask_lock, irqflags);

	return 0;
}