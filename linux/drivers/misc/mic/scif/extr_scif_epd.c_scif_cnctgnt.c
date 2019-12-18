#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  port; int /*<<< orphan*/  node; } ;
struct scifmsg {scalar_t__* payload; TYPE_2__ src; } ;
struct TYPE_6__ {scalar_t__ gnt_pld; } ;
struct TYPE_4__ {int /*<<< orphan*/  port; int /*<<< orphan*/  node; } ;
struct scif_endpt {scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  conwq; scalar_t__ remote_ep; TYPE_3__ qp_info; TYPE_1__ peer; } ;
struct scif_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ SCIFEP_CONNECTING ; 
 scalar_t__ SCIFEP_MAPPING ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void scif_cnctgnt(struct scif_dev *scifdev, struct scifmsg *msg)
{
	struct scif_endpt *ep = (struct scif_endpt *)msg->payload[0];

	spin_lock(&ep->lock);
	if (SCIFEP_CONNECTING == ep->state) {
		ep->peer.node = msg->src.node;
		ep->peer.port = msg->src.port;
		ep->qp_info.gnt_pld = msg->payload[1];
		ep->remote_ep = msg->payload[2];
		ep->state = SCIFEP_MAPPING;

		wake_up(&ep->conwq);
	}
	spin_unlock(&ep->lock);
}