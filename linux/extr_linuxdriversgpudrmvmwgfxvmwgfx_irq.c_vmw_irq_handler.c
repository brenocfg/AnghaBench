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
struct vmw_private {int /*<<< orphan*/  irqthread_pending; int /*<<< orphan*/  fifo_queue; scalar_t__ io_start; int /*<<< orphan*/  irq_mask; } ;
struct drm_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int SVGA_IRQFLAG_ANY_FENCE ; 
 int SVGA_IRQFLAG_COMMAND_BUFFER ; 
 int SVGA_IRQFLAG_ERROR ; 
 int SVGA_IRQFLAG_FENCE_GOAL ; 
 int SVGA_IRQFLAG_FIFO_PROGRESS ; 
 scalar_t__ VMWGFX_IRQSTATUS_PORT ; 
 int /*<<< orphan*/  VMW_IRQTHREAD_CMDBUF ; 
 int /*<<< orphan*/  VMW_IRQTHREAD_FENCE ; 
 int inl (scalar_t__) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vmw_private* vmw_priv (struct drm_device*) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t vmw_irq_handler(int irq, void *arg)
{
	struct drm_device *dev = (struct drm_device *)arg;
	struct vmw_private *dev_priv = vmw_priv(dev);
	uint32_t status, masked_status;
	irqreturn_t ret = IRQ_HANDLED;

	status = inl(dev_priv->io_start + VMWGFX_IRQSTATUS_PORT);
	masked_status = status & READ_ONCE(dev_priv->irq_mask);

	if (likely(status))
		outl(status, dev_priv->io_start + VMWGFX_IRQSTATUS_PORT);

	if (!status)
		return IRQ_NONE;

	if (masked_status & SVGA_IRQFLAG_FIFO_PROGRESS)
		wake_up_all(&dev_priv->fifo_queue);

	if ((masked_status & (SVGA_IRQFLAG_ANY_FENCE |
			      SVGA_IRQFLAG_FENCE_GOAL)) &&
	    !test_and_set_bit(VMW_IRQTHREAD_FENCE, dev_priv->irqthread_pending))
		ret = IRQ_WAKE_THREAD;

	if ((masked_status & (SVGA_IRQFLAG_COMMAND_BUFFER |
			      SVGA_IRQFLAG_ERROR)) &&
	    !test_and_set_bit(VMW_IRQTHREAD_CMDBUF,
			      dev_priv->irqthread_pending))
		ret = IRQ_WAKE_THREAD;

	return ret;
}