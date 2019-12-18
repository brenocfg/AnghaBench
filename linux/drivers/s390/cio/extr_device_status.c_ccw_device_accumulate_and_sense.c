#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int actl; int dstat; } ;
struct TYPE_10__ {TYPE_9__ cmd; } ;
struct irb {TYPE_1__ scsw; } ;
struct ccw_device {TYPE_8__* private; } ;
struct TYPE_16__ {scalar_t__ dosense; } ;
struct TYPE_17__ {TYPE_7__ flags; TYPE_6__* dma_area; } ;
struct TYPE_11__ {int cons; } ;
struct TYPE_12__ {TYPE_2__ erw; } ;
struct TYPE_13__ {TYPE_3__ esw0; } ;
struct TYPE_14__ {TYPE_4__ esw; } ;
struct TYPE_15__ {TYPE_5__ irb; } ;

/* Variables and functions */
 int DEV_STAT_UNIT_CHECK ; 
 int EBUSY ; 
 int SCSW_ACTL_DEVACT ; 
 int SCSW_ACTL_SCHACT ; 
 int /*<<< orphan*/  ccw_device_accumulate_irb (struct ccw_device*,struct irb*) ; 
 int /*<<< orphan*/  ccw_device_do_sense (struct ccw_device*,struct irb*) ; 

int
ccw_device_accumulate_and_sense(struct ccw_device *cdev, struct irb *irb)
{
	ccw_device_accumulate_irb(cdev, irb);
	if ((irb->scsw.cmd.actl  & (SCSW_ACTL_DEVACT | SCSW_ACTL_SCHACT)) != 0)
		return -EBUSY;
	/* Check for basic sense. */
	if (cdev->private->flags.dosense &&
	    !(irb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK)) {
		cdev->private->dma_area->irb.esw.esw0.erw.cons = 1;
		cdev->private->flags.dosense = 0;
		return 0;
	}
	if (cdev->private->flags.dosense) {
		ccw_device_do_sense(cdev, irb);
		return -EBUSY;
	}
	return 0;
}