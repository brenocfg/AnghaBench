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
struct TYPE_2__ {int /*<<< orphan*/  async_queue; } ;
struct ib_uverbs_completion_event_file {TYPE_1__ ev_queue; } ;
struct file {struct ib_uverbs_completion_event_file* private_data; } ;

/* Variables and functions */
 int fasync_helper (int,struct file*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ib_uverbs_comp_event_fasync(int fd, struct file *filp, int on)
{
	struct ib_uverbs_completion_event_file *comp_ev_file =
		filp->private_data;

	return fasync_helper(fd, filp, on, &comp_ev_file->ev_queue.async_queue);
}