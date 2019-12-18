#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  cons; } ;
struct TYPE_14__ {TYPE_1__ erw; } ;
struct TYPE_15__ {TYPE_2__ esw0; } ;
struct TYPE_19__ {int fctl; int actl; int stctl; int dstat; int cstat; int /*<<< orphan*/  count; int /*<<< orphan*/  cpa; int /*<<< orphan*/  ssi; int /*<<< orphan*/  alcc; int /*<<< orphan*/  isic; int /*<<< orphan*/  pfch; int /*<<< orphan*/  fmt; int /*<<< orphan*/  cc; int /*<<< orphan*/  sctl; int /*<<< orphan*/  key; } ;
struct TYPE_20__ {TYPE_7__ cmd; } ;
struct irb {TYPE_3__ esw; TYPE_8__ scsw; } ;
struct ccw_device {TYPE_6__* private; } ;
struct TYPE_16__ {int dosense; } ;
struct TYPE_18__ {TYPE_4__ flags; TYPE_5__* dma_area; } ;
struct TYPE_17__ {struct irb irb; } ;

/* Variables and functions */
 int DEV_STAT_BUSY ; 
 int DEV_STAT_UNIT_CHECK ; 
 int SCHN_STAT_INCORR_LEN ; 
 int SCHN_STAT_PCI ; 
 int SCSW_ACTL_DEVACT ; 
 int SCSW_ACTL_SCHACT ; 
 int SCSW_ACTL_SUSPENDED ; 
 int SCSW_FCTL_CLEAR_FUNC ; 
 int SCSW_FCTL_START_FUNC ; 
 int SCSW_STCTL_ALERT_STATUS ; 
 int SCSW_STCTL_INTER_STATUS ; 
 int SCSW_STCTL_PRIM_STATUS ; 
 int SCSW_STCTL_SEC_STATUS ; 
 int SCSW_STCTL_STATUS_PEND ; 
 int /*<<< orphan*/  ccw_device_accumulate_ecw (struct ccw_device*,struct irb*) ; 
 int /*<<< orphan*/  ccw_device_accumulate_esw (struct ccw_device*,struct irb*) ; 
 int /*<<< orphan*/  ccw_device_msg_control_check (struct ccw_device*,struct irb*) ; 
 int /*<<< orphan*/  ccw_device_path_notoper (struct ccw_device*) ; 
 int /*<<< orphan*/  memcpy (struct irb*,struct irb*,int) ; 
 int /*<<< orphan*/  memset (struct irb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scsw_is_solicited (TYPE_8__*) ; 
 scalar_t__ scsw_is_tm (TYPE_8__*) ; 
 scalar_t__ scsw_is_valid_pno (TYPE_8__*) ; 
 scalar_t__ scsw_pno (TYPE_8__*) ; 
 int scsw_stctl (TYPE_8__*) ; 

void
ccw_device_accumulate_irb(struct ccw_device *cdev, struct irb *irb)
{
	struct irb *cdev_irb;

	/*
	 * Check if the status pending bit is set in stctl.
	 * If not, the remaining bit have no meaning and we must ignore them.
	 * The esw is not meaningful as well...
	 */
	if (!(scsw_stctl(&irb->scsw) & SCSW_STCTL_STATUS_PEND))
		return;

	/* Check for channel checks and interface control checks. */
	ccw_device_msg_control_check(cdev, irb);

	/* Check for path not operational. */
	if (scsw_is_valid_pno(&irb->scsw) && scsw_pno(&irb->scsw))
		ccw_device_path_notoper(cdev);
	/* No irb accumulation for transport mode irbs. */
	if (scsw_is_tm(&irb->scsw)) {
		memcpy(&cdev->private->dma_area->irb, irb, sizeof(struct irb));
		return;
	}
	/*
	 * Don't accumulate unsolicited interrupts.
	 */
	if (!scsw_is_solicited(&irb->scsw))
		return;

	cdev_irb = &cdev->private->dma_area->irb;

	/*
	 * If the clear function had been performed, all formerly pending
	 * status at the subchannel has been cleared and we must not pass
	 * intermediate accumulated status to the device driver.
	 */
	if (irb->scsw.cmd.fctl & SCSW_FCTL_CLEAR_FUNC)
		memset(&cdev->private->dma_area->irb, 0, sizeof(struct irb));

	/* Copy bits which are valid only for the start function. */
	if (irb->scsw.cmd.fctl & SCSW_FCTL_START_FUNC) {
		/* Copy key. */
		cdev_irb->scsw.cmd.key = irb->scsw.cmd.key;
		/* Copy suspend control bit. */
		cdev_irb->scsw.cmd.sctl = irb->scsw.cmd.sctl;
		/* Accumulate deferred condition code. */
		cdev_irb->scsw.cmd.cc |= irb->scsw.cmd.cc;
		/* Copy ccw format bit. */
		cdev_irb->scsw.cmd.fmt = irb->scsw.cmd.fmt;
		/* Copy prefetch bit. */
		cdev_irb->scsw.cmd.pfch = irb->scsw.cmd.pfch;
		/* Copy initial-status-interruption-control. */
		cdev_irb->scsw.cmd.isic = irb->scsw.cmd.isic;
		/* Copy address limit checking control. */
		cdev_irb->scsw.cmd.alcc = irb->scsw.cmd.alcc;
		/* Copy suppress suspend bit. */
		cdev_irb->scsw.cmd.ssi = irb->scsw.cmd.ssi;
	}

	/* Take care of the extended control bit and extended control word. */
	ccw_device_accumulate_ecw(cdev, irb);
	    
	/* Accumulate function control. */
	cdev_irb->scsw.cmd.fctl |= irb->scsw.cmd.fctl;
	/* Copy activity control. */
	cdev_irb->scsw.cmd.actl = irb->scsw.cmd.actl;
	/* Accumulate status control. */
	cdev_irb->scsw.cmd.stctl |= irb->scsw.cmd.stctl;
	/*
	 * Copy ccw address if it is valid. This is a bit simplified
	 * but should be close enough for all practical purposes.
	 */
	if ((irb->scsw.cmd.stctl & SCSW_STCTL_PRIM_STATUS) ||
	    ((irb->scsw.cmd.stctl ==
	      (SCSW_STCTL_INTER_STATUS|SCSW_STCTL_STATUS_PEND)) &&
	     (irb->scsw.cmd.actl & SCSW_ACTL_DEVACT) &&
	     (irb->scsw.cmd.actl & SCSW_ACTL_SCHACT)) ||
	    (irb->scsw.cmd.actl & SCSW_ACTL_SUSPENDED))
		cdev_irb->scsw.cmd.cpa = irb->scsw.cmd.cpa;
	/* Accumulate device status, but not the device busy flag. */
	cdev_irb->scsw.cmd.dstat &= ~DEV_STAT_BUSY;
	/* dstat is not always valid. */
	if (irb->scsw.cmd.stctl &
	    (SCSW_STCTL_PRIM_STATUS | SCSW_STCTL_SEC_STATUS
	     | SCSW_STCTL_INTER_STATUS | SCSW_STCTL_ALERT_STATUS))
		cdev_irb->scsw.cmd.dstat |= irb->scsw.cmd.dstat;
	/* Accumulate subchannel status. */
	cdev_irb->scsw.cmd.cstat |= irb->scsw.cmd.cstat;
	/* Copy residual count if it is valid. */
	if ((irb->scsw.cmd.stctl & SCSW_STCTL_PRIM_STATUS) &&
	    (irb->scsw.cmd.cstat & ~(SCHN_STAT_PCI | SCHN_STAT_INCORR_LEN))
	     == 0)
		cdev_irb->scsw.cmd.count = irb->scsw.cmd.count;

	/* Take care of bits in the extended status word. */
	ccw_device_accumulate_esw(cdev, irb);

	/*
	 * Check whether we must issue a SENSE CCW ourselves if there is no
	 * concurrent sense facility installed for the subchannel.
	 * No sense is required if no delayed sense is pending
	 * and we did not get a unit check without sense information.
	 *
	 * Note: We should check for ioinfo[irq]->flags.consns but VM
	 *	 violates the ESA/390 architecture and doesn't present an
	 *	 operand exception for virtual devices without concurrent
	 *	 sense facility available/supported when enabling the
	 *	 concurrent sense facility.
	 */
	if ((cdev_irb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK) &&
	    !(cdev_irb->esw.esw0.erw.cons))
		cdev->private->flags.dosense = 1;
}