#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct qeth_cmd_buffer {scalar_t__ length; int /*<<< orphan*/  (* callback ) (struct qeth_card*,struct qeth_cmd_buffer*,scalar_t__) ;} ;
struct qeth_channel {struct ccw_device* ccwdev; int /*<<< orphan*/  state; int /*<<< orphan*/  irq_pending; } ;
struct qeth_card {int read_or_write_problem; int /*<<< orphan*/  wait_q; struct qeth_channel data; struct qeth_channel write; struct qeth_channel read; } ;
struct TYPE_9__ {int fctl; int cstat; int dstat; scalar_t__ count; } ;
struct TYPE_10__ {TYPE_4__ cmd; } ;
struct TYPE_6__ {scalar_t__ cons; } ;
struct TYPE_7__ {TYPE_1__ erw; } ;
struct TYPE_8__ {TYPE_2__ esw0; } ;
struct irb {TYPE_5__ scsw; struct irb* ecw; TYPE_3__ esw; } ;
struct ccwgroup_device {int /*<<< orphan*/  dev; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_DEVID (struct ccw_device*) ; 
 int /*<<< orphan*/  CH_STATE_HALTED ; 
 int /*<<< orphan*/  CH_STATE_STOPPED ; 
 int DEV_STAT_UNIT_CHECK ; 
 int DEV_STAT_UNIT_EXCEP ; 
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int EIO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 unsigned long QETH_CLEAR_CHANNEL_PARM ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int /*<<< orphan*/ ,int,int) ; 
 unsigned long QETH_HALT_CHANNEL_PARM ; 
 int SCSW_FCTL_CLEAR_FUNC ; 
 int SCSW_FCTL_HALT_FUNC ; 
 scalar_t__ __va (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,struct irb*,int,int) ; 
 int /*<<< orphan*/  qeth_cancel_cmd (struct qeth_cmd_buffer*,int) ; 
 int qeth_check_irb_error (struct qeth_card*,struct ccw_device*,struct irb*) ; 
 int /*<<< orphan*/  qeth_clear_ipacmd_list (struct qeth_card*) ; 
 int qeth_get_problem (struct qeth_card*,struct ccw_device*,struct irb*) ; 
 scalar_t__ qeth_intparm_is_iob (unsigned long) ; 
 int /*<<< orphan*/  qeth_schedule_recovery (struct qeth_card*) ; 
 int /*<<< orphan*/  stub1 (struct qeth_card*,struct qeth_cmd_buffer*,scalar_t__) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qeth_irq(struct ccw_device *cdev, unsigned long intparm,
		struct irb *irb)
{
	int rc;
	int cstat, dstat;
	struct qeth_cmd_buffer *iob = NULL;
	struct ccwgroup_device *gdev;
	struct qeth_channel *channel;
	struct qeth_card *card;

	/* while we hold the ccwdev lock, this stays valid: */
	gdev = dev_get_drvdata(&cdev->dev);
	card = dev_get_drvdata(&gdev->dev);
	if (!card)
		return;

	QETH_CARD_TEXT(card, 5, "irq");

	if (card->read.ccwdev == cdev) {
		channel = &card->read;
		QETH_CARD_TEXT(card, 5, "read");
	} else if (card->write.ccwdev == cdev) {
		channel = &card->write;
		QETH_CARD_TEXT(card, 5, "write");
	} else {
		channel = &card->data;
		QETH_CARD_TEXT(card, 5, "data");
	}

	if (qeth_intparm_is_iob(intparm))
		iob = (struct qeth_cmd_buffer *) __va((addr_t)intparm);

	rc = qeth_check_irb_error(card, cdev, irb);
	if (rc) {
		/* IO was terminated, free its resources. */
		if (iob)
			qeth_cancel_cmd(iob, rc);
		atomic_set(&channel->irq_pending, 0);
		wake_up(&card->wait_q);
		return;
	}

	atomic_set(&channel->irq_pending, 0);

	if (irb->scsw.cmd.fctl & (SCSW_FCTL_CLEAR_FUNC))
		channel->state = CH_STATE_STOPPED;

	if (irb->scsw.cmd.fctl & (SCSW_FCTL_HALT_FUNC))
		channel->state = CH_STATE_HALTED;

	if (intparm == QETH_CLEAR_CHANNEL_PARM) {
		QETH_CARD_TEXT(card, 6, "clrchpar");
		/* we don't have to handle this further */
		intparm = 0;
	}
	if (intparm == QETH_HALT_CHANNEL_PARM) {
		QETH_CARD_TEXT(card, 6, "hltchpar");
		/* we don't have to handle this further */
		intparm = 0;
	}

	cstat = irb->scsw.cmd.cstat;
	dstat = irb->scsw.cmd.dstat;

	if ((dstat & DEV_STAT_UNIT_EXCEP) ||
	    (dstat & DEV_STAT_UNIT_CHECK) ||
	    (cstat)) {
		if (irb->esw.esw0.erw.cons) {
			dev_warn(&channel->ccwdev->dev,
				"The qeth device driver failed to recover "
				"an error on the device\n");
			QETH_DBF_MESSAGE(2, "sense data available on channel %x: cstat %#X dstat %#X\n",
					 CCW_DEVID(channel->ccwdev), cstat,
					 dstat);
			print_hex_dump(KERN_WARNING, "qeth: irb ",
				DUMP_PREFIX_OFFSET, 16, 1, irb, 32, 1);
			print_hex_dump(KERN_WARNING, "qeth: sense data ",
				DUMP_PREFIX_OFFSET, 16, 1, irb->ecw, 32, 1);
		}

		rc = qeth_get_problem(card, cdev, irb);
		if (rc) {
			card->read_or_write_problem = 1;
			if (iob)
				qeth_cancel_cmd(iob, rc);
			qeth_clear_ipacmd_list(card);
			qeth_schedule_recovery(card);
			goto out;
		}
	}

	if (iob) {
		/* sanity check: */
		if (irb->scsw.cmd.count > iob->length) {
			qeth_cancel_cmd(iob, -EIO);
			goto out;
		}
		if (iob->callback)
			iob->callback(card, iob,
				      iob->length - irb->scsw.cmd.count);
	}

out:
	wake_up(&card->wait_q);
	return;
}