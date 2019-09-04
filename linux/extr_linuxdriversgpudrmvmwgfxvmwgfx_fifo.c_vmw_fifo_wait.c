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
struct vmw_private {int capabilities; int /*<<< orphan*/  fifo_queue_waiters; int /*<<< orphan*/  fifo_queue; } ;

/* Variables and functions */
 long EBUSY ; 
 int SVGA_CAP_IRQMASK ; 
 int /*<<< orphan*/  SVGA_IRQFLAG_FIFO_PROGRESS ; 
 int /*<<< orphan*/  SVGA_SYNC_FIFOFULL ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmw_fifo_is_full (struct vmw_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_fifo_ping_host (struct vmw_private*,int /*<<< orphan*/ ) ; 
 int vmw_fifo_wait_noirq (struct vmw_private*,int /*<<< orphan*/ ,int,unsigned long) ; 
 int /*<<< orphan*/  vmw_generic_waiter_add (struct vmw_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_generic_waiter_remove (struct vmw_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 long wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,unsigned long) ; 
 long wait_event_timeout (int /*<<< orphan*/ ,int,unsigned long) ; 

__attribute__((used)) static int vmw_fifo_wait(struct vmw_private *dev_priv,
			 uint32_t bytes, bool interruptible,
			 unsigned long timeout)
{
	long ret = 1L;

	if (likely(!vmw_fifo_is_full(dev_priv, bytes)))
		return 0;

	vmw_fifo_ping_host(dev_priv, SVGA_SYNC_FIFOFULL);
	if (!(dev_priv->capabilities & SVGA_CAP_IRQMASK))
		return vmw_fifo_wait_noirq(dev_priv, bytes,
					   interruptible, timeout);

	vmw_generic_waiter_add(dev_priv, SVGA_IRQFLAG_FIFO_PROGRESS,
			       &dev_priv->fifo_queue_waiters);

	if (interruptible)
		ret = wait_event_interruptible_timeout
		    (dev_priv->fifo_queue,
		     !vmw_fifo_is_full(dev_priv, bytes), timeout);
	else
		ret = wait_event_timeout
		    (dev_priv->fifo_queue,
		     !vmw_fifo_is_full(dev_priv, bytes), timeout);

	if (unlikely(ret == 0))
		ret = -EBUSY;
	else if (likely(ret > 0))
		ret = 0;

	vmw_generic_waiter_remove(dev_priv, SVGA_IRQFLAG_FIFO_PROGRESS,
				  &dev_priv->fifo_queue_waiters);

	return ret;
}