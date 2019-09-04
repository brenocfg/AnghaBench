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
struct vmw_private {int /*<<< orphan*/  fifo_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int EBUSY ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __wait ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_timeout (int) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  vmw_fifo_is_full (struct vmw_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vmw_fifo_wait_noirq(struct vmw_private *dev_priv,
			       uint32_t bytes, bool interruptible,
			       unsigned long timeout)
{
	int ret = 0;
	unsigned long end_jiffies = jiffies + timeout;
	DEFINE_WAIT(__wait);

	DRM_INFO("Fifo wait noirq.\n");

	for (;;) {
		prepare_to_wait(&dev_priv->fifo_queue, &__wait,
				(interruptible) ?
				TASK_INTERRUPTIBLE : TASK_UNINTERRUPTIBLE);
		if (!vmw_fifo_is_full(dev_priv, bytes))
			break;
		if (time_after_eq(jiffies, end_jiffies)) {
			ret = -EBUSY;
			DRM_ERROR("SVGA device lockup.\n");
			break;
		}
		schedule_timeout(1);
		if (interruptible && signal_pending(current)) {
			ret = -ERESTARTSYS;
			break;
		}
	}
	finish_wait(&dev_priv->fifo_queue, &__wait);
	wake_up_all(&dev_priv->fifo_queue);
	DRM_INFO("Fifo noirq exit.\n");
	return ret;
}