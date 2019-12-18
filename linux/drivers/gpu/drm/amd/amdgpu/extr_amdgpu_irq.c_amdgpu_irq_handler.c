#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct drm_device {int /*<<< orphan*/  dev; struct amdgpu_device* dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  ih; } ;
struct amdgpu_device {TYPE_1__ irq; } ;
typedef  scalar_t__ irqreturn_t ;

/* Variables and functions */
 scalar_t__ IRQ_HANDLED ; 
 scalar_t__ amdgpu_ih_process (struct amdgpu_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 

irqreturn_t amdgpu_irq_handler(int irq, void *arg)
{
	struct drm_device *dev = (struct drm_device *) arg;
	struct amdgpu_device *adev = dev->dev_private;
	irqreturn_t ret;

	ret = amdgpu_ih_process(adev, &adev->irq.ih);
	if (ret == IRQ_HANDLED)
		pm_runtime_mark_last_busy(dev->dev);
	return ret;
}