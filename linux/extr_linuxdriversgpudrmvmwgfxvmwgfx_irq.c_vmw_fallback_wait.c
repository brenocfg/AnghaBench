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
typedef  int /*<<< orphan*/  u32 ;
struct vmw_fifo_state {int /*<<< orphan*/  rwsem; } ;
struct vmw_private {int /*<<< orphan*/  fence_queue; int /*<<< orphan*/ * mmio_virt; int /*<<< orphan*/  marker_seq; scalar_t__ cman; struct vmw_fifo_state fifo; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ERESTARTSYS ; 
 int HZ ; 
 int SVGA_FIFO_FENCE ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __wait ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  schedule_timeout (int) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int vmw_cmdbuf_idle (scalar_t__,int,int) ; 
 int vmw_fifo_idle (struct vmw_private*,int) ; 
 int /*<<< orphan*/  vmw_mmio_write (int,int /*<<< orphan*/ *) ; 
 int vmw_seqno_passed (struct vmw_private*,int) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

int vmw_fallback_wait(struct vmw_private *dev_priv,
		      bool lazy,
		      bool fifo_idle,
		      uint32_t seqno,
		      bool interruptible,
		      unsigned long timeout)
{
	struct vmw_fifo_state *fifo_state = &dev_priv->fifo;

	uint32_t count = 0;
	uint32_t signal_seq;
	int ret;
	unsigned long end_jiffies = jiffies + timeout;
	bool (*wait_condition)(struct vmw_private *, uint32_t);
	DEFINE_WAIT(__wait);

	wait_condition = (fifo_idle) ? &vmw_fifo_idle :
		&vmw_seqno_passed;

	/**
	 * Block command submission while waiting for idle.
	 */

	if (fifo_idle) {
		down_read(&fifo_state->rwsem);
		if (dev_priv->cman) {
			ret = vmw_cmdbuf_idle(dev_priv->cman, interruptible,
					      10*HZ);
			if (ret)
				goto out_err;
		}
	}

	signal_seq = atomic_read(&dev_priv->marker_seq);
	ret = 0;

	for (;;) {
		prepare_to_wait(&dev_priv->fence_queue, &__wait,
				(interruptible) ?
				TASK_INTERRUPTIBLE : TASK_UNINTERRUPTIBLE);
		if (wait_condition(dev_priv, seqno))
			break;
		if (time_after_eq(jiffies, end_jiffies)) {
			DRM_ERROR("SVGA device lockup.\n");
			break;
		}
		if (lazy)
			schedule_timeout(1);
		else if ((++count & 0x0F) == 0) {
			/**
			 * FIXME: Use schedule_hr_timeout here for
			 * newer kernels and lower CPU utilization.
			 */

			__set_current_state(TASK_RUNNING);
			schedule();
			__set_current_state((interruptible) ?
					    TASK_INTERRUPTIBLE :
					    TASK_UNINTERRUPTIBLE);
		}
		if (interruptible && signal_pending(current)) {
			ret = -ERESTARTSYS;
			break;
		}
	}
	finish_wait(&dev_priv->fence_queue, &__wait);
	if (ret == 0 && fifo_idle) {
		u32 *fifo_mem = dev_priv->mmio_virt;

		vmw_mmio_write(signal_seq, fifo_mem + SVGA_FIFO_FENCE);
	}
	wake_up_all(&dev_priv->fence_queue);
out_err:
	if (fifo_idle)
		up_read(&fifo_state->rwsem);

	return ret;
}