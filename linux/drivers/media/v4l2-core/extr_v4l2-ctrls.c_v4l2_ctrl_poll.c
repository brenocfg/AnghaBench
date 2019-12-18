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
struct v4l2_fh {int /*<<< orphan*/  wait; } ;
struct poll_table_struct {int dummy; } ;
struct file {struct v4l2_fh* private_data; } ;
typedef  int /*<<< orphan*/  __poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLLPRI ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 
 scalar_t__ v4l2_event_pending (struct v4l2_fh*) ; 

__poll_t v4l2_ctrl_poll(struct file *file, struct poll_table_struct *wait)
{
	struct v4l2_fh *fh = file->private_data;

	poll_wait(file, &fh->wait, wait);
	if (v4l2_event_pending(fh))
		return EPOLLPRI;
	return 0;
}