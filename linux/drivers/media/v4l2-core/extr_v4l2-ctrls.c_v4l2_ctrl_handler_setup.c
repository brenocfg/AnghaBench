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
struct v4l2_ctrl_handler {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int __v4l2_ctrl_handler_setup (struct v4l2_ctrl_handler*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 

int v4l2_ctrl_handler_setup(struct v4l2_ctrl_handler *hdl)
{
	int ret;

	if (hdl == NULL)
		return 0;

	mutex_lock(hdl->lock);
	ret = __v4l2_ctrl_handler_setup(hdl);
	mutex_unlock(hdl->lock);

	return ret;
}