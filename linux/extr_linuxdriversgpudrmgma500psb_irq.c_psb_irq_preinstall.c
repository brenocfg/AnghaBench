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
struct drm_psb_private {int vdc_irq_mask; int /*<<< orphan*/  irqmask_lock; TYPE_2__* ops; } ;
struct drm_device {TYPE_1__* vblank; scalar_t__ dev_private; } ;
struct TYPE_4__ {scalar_t__ hotplug; } ;
struct TYPE_3__ {scalar_t__ enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSB_CR_EVENT_HOST_ENABLE ; 
 int /*<<< orphan*/  PSB_HWSTAM ; 
 int /*<<< orphan*/  PSB_INT_ENABLE_R ; 
 int /*<<< orphan*/  PSB_INT_MASK_R ; 
 int /*<<< orphan*/  PSB_RSGX32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSB_WSGX32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSB_WVDC32 (int,int /*<<< orphan*/ ) ; 
 int _PSB_IRQ_ASLE ; 
 int _PSB_IRQ_DISP_HOTSYNC ; 
 int _PSB_IRQ_SGX_FLAG ; 
 int _PSB_VSYNC_PIPEA_FLAG ; 
 int _PSB_VSYNC_PIPEB_FLAG ; 
 scalar_t__ gma_power_is_on (struct drm_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void psb_irq_preinstall(struct drm_device *dev)
{
	struct drm_psb_private *dev_priv =
	    (struct drm_psb_private *) dev->dev_private;
	unsigned long irqflags;

	spin_lock_irqsave(&dev_priv->irqmask_lock, irqflags);

	if (gma_power_is_on(dev)) {
		PSB_WVDC32(0xFFFFFFFF, PSB_HWSTAM);
		PSB_WVDC32(0x00000000, PSB_INT_MASK_R);
		PSB_WVDC32(0x00000000, PSB_INT_ENABLE_R);
		PSB_WSGX32(0x00000000, PSB_CR_EVENT_HOST_ENABLE);
		PSB_RSGX32(PSB_CR_EVENT_HOST_ENABLE);
	}
	if (dev->vblank[0].enabled)
		dev_priv->vdc_irq_mask |= _PSB_VSYNC_PIPEA_FLAG;
	if (dev->vblank[1].enabled)
		dev_priv->vdc_irq_mask |= _PSB_VSYNC_PIPEB_FLAG;

	/* FIXME: Handle Medfield irq mask
	if (dev->vblank[1].enabled)
		dev_priv->vdc_irq_mask |= _MDFLD_PIPEB_EVENT_FLAG;
	if (dev->vblank[2].enabled)
		dev_priv->vdc_irq_mask |= _MDFLD_PIPEC_EVENT_FLAG;
	*/

	/* Revisit this area - want per device masks ? */
	if (dev_priv->ops->hotplug)
		dev_priv->vdc_irq_mask |= _PSB_IRQ_DISP_HOTSYNC;
	dev_priv->vdc_irq_mask |= _PSB_IRQ_ASLE | _PSB_IRQ_SGX_FLAG;

	/* This register is safe even if display island is off */
	PSB_WVDC32(~dev_priv->vdc_irq_mask, PSB_INT_MASK_R);
	spin_unlock_irqrestore(&dev_priv->irqmask_lock, irqflags);
}