#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_psb_private {int vdc_irq_mask; int /*<<< orphan*/  irqmask_lock; TYPE_1__* ops; } ;
struct drm_device {TYPE_2__* vblank; struct drm_psb_private* dev_private; } ;
struct TYPE_4__ {scalar_t__ enabled; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* hotplug_enable ) (struct drm_device*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PIPE_VBLANK_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  PSB_HWSTAM ; 
 int /*<<< orphan*/  PSB_INT_ENABLE_R ; 
 int /*<<< orphan*/  PSB_INT_IDENTITY_R ; 
 int /*<<< orphan*/  PSB_INT_MASK_R ; 
 int PSB_RVDC32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSB_WVDC32 (int,int /*<<< orphan*/ ) ; 
 int _LNC_IRQ_TOPAZ_FLAG ; 
 int _PSB_IRQ_MSVDX_FLAG ; 
 int _PSB_IRQ_SGX_FLAG ; 
 int /*<<< orphan*/  psb_disable_pipestat (struct drm_psb_private*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct drm_device*,int) ; 
 int /*<<< orphan*/  wmb () ; 

void psb_irq_uninstall(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv = dev->dev_private;
	unsigned long irqflags;

	spin_lock_irqsave(&dev_priv->irqmask_lock, irqflags);

	if (dev_priv->ops->hotplug_enable)
		dev_priv->ops->hotplug_enable(dev, false);

	PSB_WVDC32(0xFFFFFFFF, PSB_HWSTAM);

	if (dev->vblank[0].enabled)
		psb_disable_pipestat(dev_priv, 0, PIPE_VBLANK_INTERRUPT_ENABLE);

	if (dev->vblank[1].enabled)
		psb_disable_pipestat(dev_priv, 1, PIPE_VBLANK_INTERRUPT_ENABLE);

	if (dev->vblank[2].enabled)
		psb_disable_pipestat(dev_priv, 2, PIPE_VBLANK_INTERRUPT_ENABLE);

	dev_priv->vdc_irq_mask &= _PSB_IRQ_SGX_FLAG |
				  _PSB_IRQ_MSVDX_FLAG |
				  _LNC_IRQ_TOPAZ_FLAG;

	/* These two registers are safe even if display island is off */
	PSB_WVDC32(~dev_priv->vdc_irq_mask, PSB_INT_MASK_R);
	PSB_WVDC32(dev_priv->vdc_irq_mask, PSB_INT_ENABLE_R);

	wmb();

	/* This register is safe even if display island is off */
	PSB_WVDC32(PSB_RVDC32(PSB_INT_IDENTITY_R), PSB_INT_IDENTITY_R);
	spin_unlock_irqrestore(&dev_priv->irqmask_lock, irqflags);
}