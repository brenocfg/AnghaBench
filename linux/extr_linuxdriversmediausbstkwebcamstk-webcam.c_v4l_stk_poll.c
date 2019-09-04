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
struct stk_camera {int /*<<< orphan*/  sio_full; int /*<<< orphan*/  wait_frame; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  is_present (struct stk_camera*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int v4l2_ctrl_poll (struct file*,int /*<<< orphan*/ *) ; 
 struct stk_camera* video_drvdata (struct file*) ; 

__attribute__((used)) static __poll_t v4l_stk_poll(struct file *fp, poll_table *wait)
{
	struct stk_camera *dev = video_drvdata(fp);
	__poll_t res = v4l2_ctrl_poll(fp, wait);

	poll_wait(fp, &dev->wait_frame, wait);

	if (!is_present(dev))
		return EPOLLERR;

	if (!list_empty(&dev->sio_full))
		return res | EPOLLIN | EPOLLRDNORM;

	return res;
}