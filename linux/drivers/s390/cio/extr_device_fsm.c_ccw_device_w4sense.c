#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct irb {int /*<<< orphan*/  scsw; } ;
struct ccw_device {TYPE_4__* private; int /*<<< orphan*/  (* handler ) (struct ccw_device*,int /*<<< orphan*/ ,struct irb*) ;} ;
typedef  enum dev_event { ____Placeholder_dev_event } dev_event ;
struct TYPE_7__ {scalar_t__ doverify; scalar_t__ dosense; } ;
struct TYPE_5__ {int /*<<< orphan*/  devno; int /*<<< orphan*/  ssid; } ;
struct TYPE_8__ {TYPE_3__ flags; int /*<<< orphan*/  wait_q; int /*<<< orphan*/  state; TYPE_2__* dma_area; TYPE_1__ dev_id; } ;
struct TYPE_6__ {int /*<<< orphan*/  irb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_MSG_EVENT (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEV_STATE_ONLINE ; 
 int SCSW_FCTL_CLEAR_FUNC ; 
 int SCSW_FCTL_HALT_FUNC ; 
 int SCSW_STCTL_ALERT_STATUS ; 
 int SCSW_STCTL_STATUS_PEND ; 
 int /*<<< orphan*/  ccw_device_accumulate_basic_sense (struct ccw_device*,struct irb*) ; 
 int /*<<< orphan*/  ccw_device_accumulate_irb (struct ccw_device*,struct irb*) ; 
 scalar_t__ ccw_device_call_handler (struct ccw_device*) ; 
 int /*<<< orphan*/  ccw_device_do_sense (struct ccw_device*,struct irb*) ; 
 int /*<<< orphan*/  ccw_device_online_verify (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cio_irb ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int scsw_cc (int /*<<< orphan*/ *) ; 
 int scsw_fctl (int /*<<< orphan*/ *) ; 
 int scsw_stctl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ccw_device*,int /*<<< orphan*/ ,struct irb*) ; 
 struct irb* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ccw_device_w4sense(struct ccw_device *cdev, enum dev_event dev_event)
{
	struct irb *irb;

	irb = this_cpu_ptr(&cio_irb);
	/* Check for unsolicited interrupt. */
	if (scsw_stctl(&irb->scsw) ==
	    (SCSW_STCTL_STATUS_PEND | SCSW_STCTL_ALERT_STATUS)) {
		if (scsw_cc(&irb->scsw) == 1)
			/* Basic sense hasn't started. Try again. */
			ccw_device_do_sense(cdev, irb);
		else {
			CIO_MSG_EVENT(0, "0.%x.%04x: unsolicited "
				      "interrupt during w4sense...\n",
				      cdev->private->dev_id.ssid,
				      cdev->private->dev_id.devno);
			if (cdev->handler)
				cdev->handler (cdev, 0, irb);
		}
		return;
	}
	/*
	 * Check if a halt or clear has been issued in the meanwhile. If yes,
	 * only deliver the halt/clear interrupt to the device driver as if it
	 * had killed the original request.
	 */
	if (scsw_fctl(&irb->scsw) &
	    (SCSW_FCTL_CLEAR_FUNC | SCSW_FCTL_HALT_FUNC)) {
		cdev->private->flags.dosense = 0;
		memset(&cdev->private->dma_area->irb, 0, sizeof(struct irb));
		ccw_device_accumulate_irb(cdev, irb);
		goto call_handler;
	}
	/* Add basic sense info to irb. */
	ccw_device_accumulate_basic_sense(cdev, irb);
	if (cdev->private->flags.dosense) {
		/* Another basic sense is needed. */
		ccw_device_do_sense(cdev, irb);
		return;
	}
call_handler:
	cdev->private->state = DEV_STATE_ONLINE;
	/* In case sensing interfered with setting the device online */
	wake_up(&cdev->private->wait_q);
	/* Call the handler. */
	if (ccw_device_call_handler(cdev) && cdev->private->flags.doverify)
		/* Start delayed path verification. */
		ccw_device_online_verify(cdev, 0);
}