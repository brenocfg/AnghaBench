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
struct scif_endpt {scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  conwq; } ;
struct scif_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ SCIFEP_BOUND ; 
 scalar_t__ SCIFEP_CONNECTING ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void scif_cnctrej(struct scif_dev *scifdev, struct scifmsg *msg)
{
	struct scif_endpt *ep = (struct scif_endpt *)msg->payload[0];

	spin_lock(&ep->lock);
	if (SCIFEP_CONNECTING == ep->state) {
		ep->state = SCIFEP_BOUND;
		wake_up(&ep->conwq);
	}
	spin_unlock(&ep->lock);
}