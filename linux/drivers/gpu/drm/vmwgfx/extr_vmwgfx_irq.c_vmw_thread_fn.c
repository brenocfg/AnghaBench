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
struct vmw_private {int /*<<< orphan*/  cman; int /*<<< orphan*/  irqthread_pending; int /*<<< orphan*/  fence_queue; int /*<<< orphan*/  fman; } ;
struct drm_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  VMW_IRQTHREAD_CMDBUF ; 
 int /*<<< orphan*/  VMW_IRQTHREAD_FENCE ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_cmdbuf_irqthread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_fences_update (int /*<<< orphan*/ ) ; 
 struct vmw_private* vmw_priv (struct drm_device*) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t vmw_thread_fn(int irq, void *arg)
{
	struct drm_device *dev = (struct drm_device *)arg;
	struct vmw_private *dev_priv = vmw_priv(dev);
	irqreturn_t ret = IRQ_NONE;

	if (test_and_clear_bit(VMW_IRQTHREAD_FENCE,
			       dev_priv->irqthread_pending)) {
		vmw_fences_update(dev_priv->fman);
		wake_up_all(&dev_priv->fence_queue);
		ret = IRQ_HANDLED;
	}

	if (test_and_clear_bit(VMW_IRQTHREAD_CMDBUF,
			       dev_priv->irqthread_pending)) {
		vmw_cmdbuf_irqthread(dev_priv->cman);
		ret = IRQ_HANDLED;
	}

	return ret;
}