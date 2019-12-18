#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct si476x_radio {TYPE_1__* core; } ;
struct poll_table_struct {int dummy; } ;
struct file {int dummy; } ;
typedef  int __poll_t ;
struct TYPE_2__ {int /*<<< orphan*/  rds_fifo; int /*<<< orphan*/  is_alive; int /*<<< orphan*/  rds_read_queue; } ;

/* Variables and functions */
 int EPOLLHUP ; 
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfifo_is_empty (int /*<<< orphan*/ *) ; 
 int poll_requested_events (struct poll_table_struct*) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 
 int v4l2_ctrl_poll (struct file*,struct poll_table_struct*) ; 
 struct si476x_radio* video_drvdata (struct file*) ; 

__attribute__((used)) static __poll_t si476x_radio_fops_poll(struct file *file,
				struct poll_table_struct *pts)
{
	struct si476x_radio *radio = video_drvdata(file);
	__poll_t req_events = poll_requested_events(pts);
	__poll_t err = v4l2_ctrl_poll(file, pts);

	if (req_events & (EPOLLIN | EPOLLRDNORM)) {
		if (atomic_read(&radio->core->is_alive))
			poll_wait(file, &radio->core->rds_read_queue, pts);

		if (!atomic_read(&radio->core->is_alive))
			err = EPOLLHUP;

		if (!kfifo_is_empty(&radio->core->rds_fifo))
			err = EPOLLIN | EPOLLRDNORM;
	}

	return err;
}