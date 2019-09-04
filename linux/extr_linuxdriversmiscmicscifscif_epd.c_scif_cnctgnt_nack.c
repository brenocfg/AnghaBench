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
struct scifmsg {scalar_t__* payload; } ;
struct scif_endpt {int /*<<< orphan*/  lock; int /*<<< orphan*/  conwq; int /*<<< orphan*/  state; } ;
struct scif_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCIFEP_CLOSING ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void scif_cnctgnt_nack(struct scif_dev *scifdev, struct scifmsg *msg)
{
	struct scif_endpt *ep = (struct scif_endpt *)msg->payload[0];

	spin_lock(&ep->lock);
	ep->state = SCIFEP_CLOSING;
	wake_up(&ep->conwq);
	spin_unlock(&ep->lock);
}