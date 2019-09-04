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
struct ishtp_cl_rb {int /*<<< orphan*/  list; struct ishtp_cl* cl; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; } ;
struct ishtp_cl {int /*<<< orphan*/  out_flow_ctrl_creds; int /*<<< orphan*/  free_list_spinlock; TYPE_1__ free_rb_list; } ;

/* Variables and functions */
 int EFAULT ; 
 int ishtp_cl_read_start (struct ishtp_cl*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ishtp_cl_io_rb_recycle(struct ishtp_cl_rb *rb)
{
	struct ishtp_cl *cl;
	int	rets = 0;
	unsigned long	flags;

	if (!rb || !rb->cl)
		return	-EFAULT;

	cl = rb->cl;
	spin_lock_irqsave(&cl->free_list_spinlock, flags);
	list_add_tail(&rb->list, &cl->free_rb_list.list);
	spin_unlock_irqrestore(&cl->free_list_spinlock, flags);

	/*
	 * If we returned the first buffer to empty 'free' list,
	 * send flow control
	 */
	if (!cl->out_flow_ctrl_creds)
		rets = ishtp_cl_read_start(cl);

	return	rets;
}