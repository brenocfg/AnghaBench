#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  cons; } ;
struct TYPE_12__ {TYPE_2__ erw; } ;
struct TYPE_13__ {TYPE_3__ esw0; } ;
struct TYPE_10__ {int dstat; } ;
struct TYPE_17__ {TYPE_1__ cmd; } ;
struct irb {TYPE_4__ esw; TYPE_8__ scsw; } ;
struct ccw_device {TYPE_7__* private; int /*<<< orphan*/  (* handler ) (struct ccw_device*,int /*<<< orphan*/ ,struct irb*) ;} ;
typedef  enum dev_event { ____Placeholder_dev_event } dev_event ;
struct TYPE_15__ {scalar_t__ doverify; scalar_t__ dosense; } ;
struct TYPE_16__ {TYPE_6__ flags; void* state; scalar_t__ intparm; TYPE_5__* dma_area; } ;
struct TYPE_14__ {int /*<<< orphan*/  irb; } ;

/* Variables and functions */
 void* DEV_STATE_W4SENSE ; 
 int DEV_STAT_UNIT_CHECK ; 
 int /*<<< orphan*/  ccw_device_accumulate_irb (struct ccw_device*,struct irb*) ; 
 scalar_t__ ccw_device_call_handler (struct ccw_device*) ; 
 scalar_t__ ccw_device_do_sense (struct ccw_device*,struct irb*) ; 
 int /*<<< orphan*/  ccw_device_online_verify (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cio_irb ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct irb*,int) ; 
 int /*<<< orphan*/  scsw_is_solicited (TYPE_8__*) ; 
 int /*<<< orphan*/  scsw_is_tm (TYPE_8__*) ; 
 int /*<<< orphan*/  stub1 (struct ccw_device*,int /*<<< orphan*/ ,struct irb*) ; 
 struct irb* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ccw_device_irq(struct ccw_device *cdev, enum dev_event dev_event)
{
	struct irb *irb;
	int is_cmd;

	irb = this_cpu_ptr(&cio_irb);
	is_cmd = !scsw_is_tm(&irb->scsw);
	/* Check for unsolicited interrupt. */
	if (!scsw_is_solicited(&irb->scsw)) {
		if (is_cmd && (irb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK) &&
		    !irb->esw.esw0.erw.cons) {
			/* Unit check but no sense data. Need basic sense. */
			if (ccw_device_do_sense(cdev, irb) != 0)
				goto call_handler_unsol;
			memcpy(&cdev->private->dma_area->irb, irb,
			       sizeof(struct irb));
			cdev->private->state = DEV_STATE_W4SENSE;
			cdev->private->intparm = 0;
			return;
		}
call_handler_unsol:
		if (cdev->handler)
			cdev->handler (cdev, 0, irb);
		if (cdev->private->flags.doverify)
			ccw_device_online_verify(cdev, 0);
		return;
	}
	/* Accumulate status and find out if a basic sense is needed. */
	ccw_device_accumulate_irb(cdev, irb);
	if (is_cmd && cdev->private->flags.dosense) {
		if (ccw_device_do_sense(cdev, irb) == 0) {
			cdev->private->state = DEV_STATE_W4SENSE;
		}
		return;
	}
	/* Call the handler. */
	if (ccw_device_call_handler(cdev) && cdev->private->flags.doverify)
		/* Start delayed path verification. */
		ccw_device_online_verify(cdev, 0);
}