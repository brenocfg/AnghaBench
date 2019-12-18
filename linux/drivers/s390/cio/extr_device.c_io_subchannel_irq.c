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
struct subchannel {int /*<<< orphan*/  dev; } ;
struct ccw_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_TRACE_EVENT (int,char*) ; 
 int /*<<< orphan*/  DEV_EVENT_INTERRUPT ; 
 int /*<<< orphan*/  IRQIO_CIO ; 
 int /*<<< orphan*/  dev_fsm_event (struct ccw_device*,int /*<<< orphan*/ ) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inc_irq_stat (int /*<<< orphan*/ ) ; 
 struct ccw_device* sch_get_cdev (struct subchannel*) ; 

__attribute__((used)) static void io_subchannel_irq(struct subchannel *sch)
{
	struct ccw_device *cdev;

	cdev = sch_get_cdev(sch);

	CIO_TRACE_EVENT(6, "IRQ");
	CIO_TRACE_EVENT(6, dev_name(&sch->dev));
	if (cdev)
		dev_fsm_event(cdev, DEV_EVENT_INTERRUPT);
	else
		inc_irq_stat(IRQIO_CIO);
}