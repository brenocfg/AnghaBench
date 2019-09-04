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
struct scifmsg {scalar_t__ uop; } ;
struct scif_qp {int /*<<< orphan*/  inbound_q; } ;
struct scif_dev {int dummy; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 scalar_t__ SCIF_EXIT_ACK ; 
 int /*<<< orphan*/  scif_nodeqp_msg_handler (struct scif_dev*,struct scif_qp*,struct scifmsg*) ; 
 int scif_rb_get_next (int /*<<< orphan*/ *,struct scifmsg*,int) ; 
 int /*<<< orphan*/  scif_rb_update_read_ptr (int /*<<< orphan*/ *) ; 

void scif_nodeqp_intrhandler(struct scif_dev *scifdev, struct scif_qp *qp)
{
	struct scifmsg msg;
	int read_size;

	do {
		read_size = scif_rb_get_next(&qp->inbound_q, &msg, sizeof(msg));
		if (!read_size)
			break;
		scif_nodeqp_msg_handler(scifdev, qp, &msg);
		/*
		 * The node queue pair is unmapped so skip the read pointer
		 * update after receipt of a SCIF_EXIT_ACK
		 */
		if (SCIF_EXIT_ACK == msg.uop)
			break;
		scif_rb_update_read_ptr(&qp->inbound_q);
	} while (1);
}