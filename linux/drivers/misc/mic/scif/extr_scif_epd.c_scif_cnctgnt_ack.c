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
struct scifmsg {scalar_t__* payload; } ;
struct scif_endpt {int /*<<< orphan*/  lock; int /*<<< orphan*/  conwq; int /*<<< orphan*/  list; int /*<<< orphan*/  state; } ;
struct scif_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  connlock; int /*<<< orphan*/  connected; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCIFEP_CONNECTED ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ scif_info ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void scif_cnctgnt_ack(struct scif_dev *scifdev, struct scifmsg *msg)
{
	struct scif_endpt *ep = (struct scif_endpt *)msg->payload[0];

	mutex_lock(&scif_info.connlock);
	spin_lock(&ep->lock);
	/* New ep is now connected with all resources set. */
	ep->state = SCIFEP_CONNECTED;
	list_add_tail(&ep->list, &scif_info.connected);
	wake_up(&ep->conwq);
	spin_unlock(&ep->lock);
	mutex_unlock(&scif_info.connlock);
}