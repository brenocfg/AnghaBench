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
struct drm_device {int irq_enabled; int irq; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  VMWGFX_DRIVER_NAME ; 
 int request_threaded_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_device*) ; 
 int /*<<< orphan*/  vmw_irq_handler ; 
 int /*<<< orphan*/  vmw_irq_preinstall (struct drm_device*) ; 
 int /*<<< orphan*/  vmw_thread_fn ; 

int vmw_irq_install(struct drm_device *dev, int irq)
{
	int ret;

	if (dev->irq_enabled)
		return -EBUSY;

	vmw_irq_preinstall(dev);

	ret = request_threaded_irq(irq, vmw_irq_handler, vmw_thread_fn,
				   IRQF_SHARED, VMWGFX_DRIVER_NAME, dev);
	if (ret < 0)
		return ret;

	dev->irq_enabled = true;
	dev->irq = irq;

	return ret;
}