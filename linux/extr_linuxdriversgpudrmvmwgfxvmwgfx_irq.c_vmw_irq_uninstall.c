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
typedef  int /*<<< orphan*/  uint32_t ;
struct vmw_private {int capabilities; scalar_t__ io_start; } ;
struct drm_device {int irq_enabled; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int SVGA_CAP_IRQMASK ; 
 int /*<<< orphan*/  SVGA_REG_IRQMASK ; 
 scalar_t__ VMWGFX_IRQSTATUS_PORT ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct drm_device*) ; 
 int /*<<< orphan*/  inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 
 struct vmw_private* vmw_priv (struct drm_device*) ; 
 int /*<<< orphan*/  vmw_write (struct vmw_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vmw_irq_uninstall(struct drm_device *dev)
{
	struct vmw_private *dev_priv = vmw_priv(dev);
	uint32_t status;

	if (!(dev_priv->capabilities & SVGA_CAP_IRQMASK))
		return;

	if (!dev->irq_enabled)
		return;

	vmw_write(dev_priv, SVGA_REG_IRQMASK, 0);

	status = inl(dev_priv->io_start + VMWGFX_IRQSTATUS_PORT);
	outl(status, dev_priv->io_start + VMWGFX_IRQSTATUS_PORT);

	dev->irq_enabled = false;
	free_irq(dev->irq, dev);
}