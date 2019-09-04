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
struct stk1160 {int /*<<< orphan*/  v4l_lock; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int /*<<< orphan*/  keep_buffers ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stk1160_cancel_isoc (struct stk1160*) ; 
 int /*<<< orphan*/  stk1160_clear_queue (struct stk1160*) ; 
 int /*<<< orphan*/  stk1160_dbg (char*) ; 
 int /*<<< orphan*/  stk1160_free_isoc (struct stk1160*) ; 
 int /*<<< orphan*/  stk1160_stop_hw (struct stk1160*) ; 

__attribute__((used)) static int stk1160_stop_streaming(struct stk1160 *dev)
{
	if (mutex_lock_interruptible(&dev->v4l_lock))
		return -ERESTARTSYS;

	/*
	 * Once URBs are cancelled, the URB complete handler
	 * won't be running. This is required to safely release the
	 * current buffer (dev->isoc_ctl.buf).
	 */
	stk1160_cancel_isoc(dev);

	/*
	 * It is possible to keep buffers around using a module parameter.
	 * This is intended to avoid memory fragmentation.
	 */
	if (!keep_buffers)
		stk1160_free_isoc(dev);

	stk1160_stop_hw(dev);

	stk1160_clear_queue(dev);

	stk1160_dbg("streaming stopped\n");

	mutex_unlock(&dev->v4l_lock);

	return 0;
}