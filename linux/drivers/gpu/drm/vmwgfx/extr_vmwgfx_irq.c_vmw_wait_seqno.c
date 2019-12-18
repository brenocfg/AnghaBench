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
typedef  scalar_t__ uint32_t ;
struct vmw_fifo_state {int capabilities; } ;
struct vmw_private {scalar_t__ last_read_seqno; int capabilities; int /*<<< orphan*/  fence_queue; struct vmw_fifo_state fifo; } ;

/* Variables and functions */
 long EBUSY ; 
 int SVGA_CAP_IRQMASK ; 
 int SVGA_FIFO_CAP_FENCE ; 
 int /*<<< orphan*/  SVGA_SYNC_GENERIC ; 
 scalar_t__ VMW_FENCE_WRAP ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 
 int vmw_fallback_wait (struct vmw_private*,int,int,scalar_t__,int,unsigned long) ; 
 int /*<<< orphan*/  vmw_fifo_ping_host (struct vmw_private*,int /*<<< orphan*/ ) ; 
 int vmw_seqno_passed (struct vmw_private*,scalar_t__) ; 
 int /*<<< orphan*/  vmw_seqno_waiter_add (struct vmw_private*) ; 
 int /*<<< orphan*/  vmw_seqno_waiter_remove (struct vmw_private*) ; 
 long wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,unsigned long) ; 
 long wait_event_timeout (int /*<<< orphan*/ ,int,unsigned long) ; 

int vmw_wait_seqno(struct vmw_private *dev_priv,
		      bool lazy, uint32_t seqno,
		      bool interruptible, unsigned long timeout)
{
	long ret;
	struct vmw_fifo_state *fifo = &dev_priv->fifo;

	if (likely(dev_priv->last_read_seqno - seqno < VMW_FENCE_WRAP))
		return 0;

	if (likely(vmw_seqno_passed(dev_priv, seqno)))
		return 0;

	vmw_fifo_ping_host(dev_priv, SVGA_SYNC_GENERIC);

	if (!(fifo->capabilities & SVGA_FIFO_CAP_FENCE))
		return vmw_fallback_wait(dev_priv, lazy, true, seqno,
					 interruptible, timeout);

	if (!(dev_priv->capabilities & SVGA_CAP_IRQMASK))
		return vmw_fallback_wait(dev_priv, lazy, false, seqno,
					 interruptible, timeout);

	vmw_seqno_waiter_add(dev_priv);

	if (interruptible)
		ret = wait_event_interruptible_timeout
		    (dev_priv->fence_queue,
		     vmw_seqno_passed(dev_priv, seqno),
		     timeout);
	else
		ret = wait_event_timeout
		    (dev_priv->fence_queue,
		     vmw_seqno_passed(dev_priv, seqno),
		     timeout);

	vmw_seqno_waiter_remove(dev_priv);

	if (unlikely(ret == 0))
		ret = -EBUSY;
	else if (likely(ret > 0))
		ret = 0;

	return ret;
}