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
struct vmw_private {scalar_t__ io_start; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ VMWGFX_IRQSTATUS_PORT ; 
 int /*<<< orphan*/  inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 
 struct vmw_private* vmw_priv (struct drm_device*) ; 

__attribute__((used)) static void vmw_irq_preinstall(struct drm_device *dev)
{
	struct vmw_private *dev_priv = vmw_priv(dev);
	uint32_t status;

	status = inl(dev_priv->io_start + VMWGFX_IRQSTATUS_PORT);
	outl(status, dev_priv->io_start + VMWGFX_IRQSTATUS_PORT);
}