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
struct scifmsg {int dummy; } ;
struct scif_qp {int /*<<< orphan*/  inbound_q; int /*<<< orphan*/  recv_lock; } ;
struct scif_loopb_msg {int /*<<< orphan*/  list; int /*<<< orphan*/  msg; } ;
struct scif_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  loopb_work; int /*<<< orphan*/  loopb_wq; int /*<<< orphan*/  loopb_recv_q; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct scif_loopb_msg*) ; 
 struct scif_loopb_msg* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ scif_info ; 
 int scif_rb_get_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  scif_rb_update_read_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int
scif_loopb_msg_handler(struct scif_dev *scifdev, struct scif_qp *qp)
{
	int read_size;
	struct scif_loopb_msg *msg;

	do {
		msg = kmalloc(sizeof(*msg), GFP_KERNEL);
		if (!msg)
			return -ENOMEM;
		read_size = scif_rb_get_next(&qp->inbound_q, &msg->msg,
					     sizeof(struct scifmsg));
		if (read_size != sizeof(struct scifmsg)) {
			kfree(msg);
			scif_rb_update_read_ptr(&qp->inbound_q);
			break;
		}
		spin_lock(&qp->recv_lock);
		list_add_tail(&msg->list, &scif_info.loopb_recv_q);
		spin_unlock(&qp->recv_lock);
		queue_work(scif_info.loopb_wq, &scif_info.loopb_work);
		scif_rb_update_read_ptr(&qp->inbound_q);
	} while (read_size == sizeof(struct scifmsg));
	return read_size;
}