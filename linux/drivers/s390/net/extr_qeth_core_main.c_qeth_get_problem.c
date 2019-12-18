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
struct qeth_card {int dummy; } ;
struct TYPE_3__ {int cstat; int dstat; } ;
struct TYPE_4__ {TYPE_1__ cmd; } ;
struct irb {TYPE_2__ scsw; scalar_t__ ecw; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_DEVID (struct ccw_device*) ; 
 int DEV_STAT_UNIT_CHECK ; 
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int /*<<< orphan*/ ,int,int) ; 
 int SCHN_STAT_CHAIN_CHECK ; 
 int SCHN_STAT_CHN_CTRL_CHK ; 
 int SCHN_STAT_CHN_DATA_CHK ; 
 int SCHN_STAT_INTF_CTRL_CHK ; 
 int SCHN_STAT_PROG_CHECK ; 
 int SCHN_STAT_PROT_CHECK ; 
 size_t SENSE_COMMAND_REJECT_BYTE ; 
 char SENSE_COMMAND_REJECT_FLAG ; 
 size_t SENSE_RESETTING_EVENT_BYTE ; 
 char SENSE_RESETTING_EVENT_FLAG ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,struct irb*,int,int) ; 

__attribute__((used)) static int qeth_get_problem(struct qeth_card *card, struct ccw_device *cdev,
			    struct irb *irb)
{
	int dstat, cstat;
	char *sense;

	sense = (char *) irb->ecw;
	cstat = irb->scsw.cmd.cstat;
	dstat = irb->scsw.cmd.dstat;

	if (cstat & (SCHN_STAT_CHN_CTRL_CHK | SCHN_STAT_INTF_CTRL_CHK |
		     SCHN_STAT_CHN_DATA_CHK | SCHN_STAT_CHAIN_CHECK |
		     SCHN_STAT_PROT_CHECK | SCHN_STAT_PROG_CHECK)) {
		QETH_CARD_TEXT(card, 2, "CGENCHK");
		dev_warn(&cdev->dev, "The qeth device driver "
			"failed to recover an error on the device\n");
		QETH_DBF_MESSAGE(2, "check on channel %x with dstat=%#x, cstat=%#x\n",
				 CCW_DEVID(cdev), dstat, cstat);
		print_hex_dump(KERN_WARNING, "qeth: irb ", DUMP_PREFIX_OFFSET,
				16, 1, irb, 64, 1);
		return 1;
	}

	if (dstat & DEV_STAT_UNIT_CHECK) {
		if (sense[SENSE_RESETTING_EVENT_BYTE] &
		    SENSE_RESETTING_EVENT_FLAG) {
			QETH_CARD_TEXT(card, 2, "REVIND");
			return 1;
		}
		if (sense[SENSE_COMMAND_REJECT_BYTE] &
		    SENSE_COMMAND_REJECT_FLAG) {
			QETH_CARD_TEXT(card, 2, "CMDREJi");
			return 1;
		}
		if ((sense[2] == 0xaf) && (sense[3] == 0xfe)) {
			QETH_CARD_TEXT(card, 2, "AFFE");
			return 1;
		}
		if ((!sense[0]) && (!sense[1]) && (!sense[2]) && (!sense[3])) {
			QETH_CARD_TEXT(card, 2, "ZEROSEN");
			return 0;
		}
		QETH_CARD_TEXT(card, 2, "DGENCHK");
			return 1;
	}
	return 0;
}