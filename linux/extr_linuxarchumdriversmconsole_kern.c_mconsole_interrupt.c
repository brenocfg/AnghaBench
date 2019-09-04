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
struct mc_request {int /*<<< orphan*/  regs; TYPE_1__* cmd; } ;
struct mconsole_entry {int /*<<< orphan*/  list; struct mc_request request; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  regs; } ;
struct TYPE_3__ {scalar_t__ context; int /*<<< orphan*/  (* handler ) (struct mc_request*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ MCONSOLE_INTR ; 
 int /*<<< orphan*/  MCONSOLE_IRQ ; 
 TYPE_2__* get_irq_regs () ; 
 struct mconsole_entry* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mc_requests ; 
 scalar_t__ mconsole_get_request (long,struct mc_request*) ; 
 int /*<<< orphan*/  mconsole_reply (struct mc_request*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mconsole_work ; 
 int /*<<< orphan*/  reactivate_fd (long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mc_request*) ; 

__attribute__((used)) static irqreturn_t mconsole_interrupt(int irq, void *dev_id)
{
	/* long to avoid size mismatch warnings from gcc */
	long fd;
	struct mconsole_entry *new;
	static struct mc_request req;	/* that's OK */

	fd = (long) dev_id;
	while (mconsole_get_request(fd, &req)) {
		if (req.cmd->context == MCONSOLE_INTR)
			(*req.cmd->handler)(&req);
		else {
			new = kmalloc(sizeof(*new), GFP_NOWAIT);
			if (new == NULL)
				mconsole_reply(&req, "Out of memory", 1, 0);
			else {
				new->request = req;
				new->request.regs = get_irq_regs()->regs;
				list_add(&new->list, &mc_requests);
			}
		}
	}
	if (!list_empty(&mc_requests))
		schedule_work(&mconsole_work);
	reactivate_fd(fd, MCONSOLE_IRQ);
	return IRQ_HANDLED;
}