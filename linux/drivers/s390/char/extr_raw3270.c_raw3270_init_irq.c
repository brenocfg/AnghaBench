#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct raw3270_view {struct raw3270* dev; } ;
struct raw3270_request {int /*<<< orphan*/  rc; } ;
struct raw3270 {int dummy; } ;
struct TYPE_4__ {int dstat; } ;
struct TYPE_3__ {TYPE_2__ cmd; } ;
struct irb {int* ecw; TYPE_1__ scsw; } ;

/* Variables and functions */
 int DEV_STAT_ATTENTION ; 
 int DEV_STAT_UNIT_CHECK ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int SNS0_CMD_REJECT ; 
 int /*<<< orphan*/  raw3270_read_modified (struct raw3270*) ; 

__attribute__((used)) static void
raw3270_init_irq(struct raw3270_view *view, struct raw3270_request *rq,
		 struct irb *irb)
{
	struct raw3270 *rp;

	if (rq) {
		if (irb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK) {
			if (irb->ecw[0] & SNS0_CMD_REJECT)
				rq->rc = -EOPNOTSUPP;
			else
				rq->rc = -EIO;
		}
	}
	if (irb->scsw.cmd.dstat & DEV_STAT_ATTENTION) {
		/* Queue read modified after attention interrupt */
		rp = view->dev;
		raw3270_read_modified(rp);
	}
}