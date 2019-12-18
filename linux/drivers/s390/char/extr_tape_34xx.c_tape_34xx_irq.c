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
struct tape_request {scalar_t__ op; int /*<<< orphan*/  rescnt; } ;
struct tape_device {int dummy; } ;
struct TYPE_3__ {int dstat; } ;
struct TYPE_4__ {TYPE_1__ cmd; } ;
struct irb {TYPE_2__ scsw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_EVENT (int,char*) ; 
 int DEV_STAT_DEV_END ; 
 int DEV_STAT_UNIT_CHECK ; 
 int DEV_STAT_UNIT_EXCEP ; 
 int /*<<< orphan*/  ENOSPC ; 
 int TAPE_IO_STOP ; 
 scalar_t__ TO_BSB ; 
 scalar_t__ TO_FSB ; 
 scalar_t__ TO_WRI ; 
 int tape_34xx_done (struct tape_request*) ; 
 int tape_34xx_erp_failed (struct tape_request*,int /*<<< orphan*/ ) ; 
 int tape_34xx_unit_check (struct tape_device*,struct tape_request*,struct irb*) ; 
 int tape_34xx_unsolicited_irq (struct tape_device*,struct irb*) ; 
 int /*<<< orphan*/  tape_dump_sense_dbf (struct tape_device*,struct tape_request*,struct irb*) ; 

__attribute__((used)) static int
tape_34xx_irq(struct tape_device *device, struct tape_request *request,
	      struct irb *irb)
{
	if (request == NULL)
		return tape_34xx_unsolicited_irq(device, irb);

	if ((irb->scsw.cmd.dstat & DEV_STAT_UNIT_EXCEP) &&
	    (irb->scsw.cmd.dstat & DEV_STAT_DEV_END) &&
	    (request->op == TO_WRI)) {
		/* Write at end of volume */
		return tape_34xx_erp_failed(request, -ENOSPC);
	}

	if (irb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK)
		return tape_34xx_unit_check(device, request, irb);

	if (irb->scsw.cmd.dstat & DEV_STAT_DEV_END) {
		/*
		 * A unit exception occurs on skipping over a tapemark block.
		 */
		if (irb->scsw.cmd.dstat & DEV_STAT_UNIT_EXCEP) {
			if (request->op == TO_BSB || request->op == TO_FSB)
				request->rescnt++;
			else
				DBF_EVENT(5, "Unit Exception!\n");
		}
		return tape_34xx_done(request);
	}

	DBF_EVENT(6, "xunknownirq\n");
	tape_dump_sense_dbf(device, request, irb);
	return TAPE_IO_STOP;
}