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
struct scifmsg {scalar_t__* payload; int /*<<< orphan*/  uop; } ;
struct scif_endpt {int /*<<< orphan*/  remote_dev; scalar_t__ remote_ep; } ;
struct scif_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_SIG_ACK ; 
 int /*<<< orphan*/  SCIF_SIG_NACK ; 
 int /*<<< orphan*/  SCIF_WINDOW_PEER ; 
 int /*<<< orphan*/  scif_nodeqp_send (int /*<<< orphan*/ ,struct scifmsg*) ; 
 int scif_prog_signal (struct scif_endpt*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

void scif_recv_sig_remote(struct scif_dev *scifdev, struct scifmsg *msg)
{
	struct scif_endpt *ep = (struct scif_endpt *)msg->payload[0];
	int err;

	err = scif_prog_signal(ep, msg->payload[1], msg->payload[2],
			       SCIF_WINDOW_PEER);
	if (err)
		msg->uop = SCIF_SIG_NACK;
	else
		msg->uop = SCIF_SIG_ACK;
	msg->payload[0] = ep->remote_ep;
	scif_nodeqp_send(ep->remote_dev, msg);
}