#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct drm_device {scalar_t__ dev_private; } ;
struct TYPE_6__ {int irq_enable_mask; } ;
typedef  TYPE_1__ drm_via_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int EINVAL ; 
 int VIA_IRQ_GLOBAL ; 
 int /*<<< orphan*/  VIA_REG_INTERRUPT ; 
 int via_read (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  via_write (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  via_write8 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  via_write8_mask (TYPE_1__*,int,int,int) ; 

int via_driver_irq_postinstall(struct drm_device *dev)
{
	drm_via_private_t *dev_priv = (drm_via_private_t *) dev->dev_private;
	u32 status;

	DRM_DEBUG("via_driver_irq_postinstall\n");
	if (!dev_priv)
		return -EINVAL;

	status = via_read(dev_priv, VIA_REG_INTERRUPT);
	via_write(dev_priv, VIA_REG_INTERRUPT, status | VIA_IRQ_GLOBAL
		  | dev_priv->irq_enable_mask);

	/* Some magic, oh for some data sheets ! */
	via_write8(dev_priv, 0x83d4, 0x11);
	via_write8_mask(dev_priv, 0x83d5, 0x30, 0x30);

	return 0;
}