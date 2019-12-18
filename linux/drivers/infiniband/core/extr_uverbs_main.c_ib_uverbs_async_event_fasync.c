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
struct ib_uverbs_event_queue {int /*<<< orphan*/  async_queue; } ;
struct file {struct ib_uverbs_event_queue* private_data; } ;

/* Variables and functions */
 int fasync_helper (int,struct file*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ib_uverbs_async_event_fasync(int fd, struct file *filp, int on)
{
	struct ib_uverbs_event_queue *ev_queue = filp->private_data;

	return fasync_helper(fd, filp, on, &ev_queue->async_queue);
}