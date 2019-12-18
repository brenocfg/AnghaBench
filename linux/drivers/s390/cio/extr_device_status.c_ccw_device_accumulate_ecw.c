#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int stctl; scalar_t__ ectl; } ;
struct TYPE_9__ {TYPE_1__ cmd; } ;
struct irb {int /*<<< orphan*/  ecw; TYPE_2__ scsw; } ;
struct ccw_device {TYPE_7__* private; } ;
struct TYPE_14__ {TYPE_6__* dma_area; } ;
struct TYPE_10__ {scalar_t__ ectl; } ;
struct TYPE_11__ {TYPE_3__ cmd; } ;
struct TYPE_12__ {int /*<<< orphan*/  ecw; TYPE_4__ scsw; } ;
struct TYPE_13__ {TYPE_5__ irb; } ;

/* Variables and functions */
 int SCSW_STCTL_ALERT_STATUS ; 
 int SCSW_STCTL_INTER_STATUS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ccw_device_accumulate_ecw(struct ccw_device *cdev, struct irb *irb)
{
	/*
	 * Copy extended control bit if it is valid... yes there
	 * are condition that have to be met for the extended control
	 * bit to have meaning. Sick.
	 */
	cdev->private->dma_area->irb.scsw.cmd.ectl = 0;
	if ((irb->scsw.cmd.stctl & SCSW_STCTL_ALERT_STATUS) &&
	    !(irb->scsw.cmd.stctl & SCSW_STCTL_INTER_STATUS))
		cdev->private->dma_area->irb.scsw.cmd.ectl = irb->scsw.cmd.ectl;
	/* Check if extended control word is valid. */
	if (!cdev->private->dma_area->irb.scsw.cmd.ectl)
		return;
	/* Copy concurrent sense / model dependent information. */
	memcpy(&cdev->private->dma_area->irb.ecw, irb->ecw, sizeof(irb->ecw));
}