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
struct TYPE_5__ {int command; int /*<<< orphan*/  return_code; } ;
struct qeth_ipa_cmd {TYPE_1__ hdr; } ;
struct TYPE_7__ {int hwtrap; int /*<<< orphan*/  chpid; } ;
struct qeth_card {TYPE_4__* discipline; TYPE_3__ info; TYPE_2__* gdev; int /*<<< orphan*/  dev; int /*<<< orphan*/  close_dev_work; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* control_event_handler ) (struct qeth_card*,struct qeth_ipa_cmd*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  IPA_CMD_ADDRESS_CHANGE_NOTIF 135 
 int IPA_CMD_DELCCID ; 
#define  IPA_CMD_MODCCID 134 
#define  IPA_CMD_REGISTER_LOCAL_ADDR 133 
#define  IPA_CMD_SETBRIDGEPORT_IQD 132 
#define  IPA_CMD_SETBRIDGEPORT_OSA 131 
 int IPA_CMD_SETCCID ; 
 int IPA_CMD_SET_DIAG_ASS ; 
#define  IPA_CMD_STARTLAN 130 
#define  IPA_CMD_STOPLAN 129 
#define  IPA_CMD_UNREGISTER_LOCAL_ADDR 128 
 int /*<<< orphan*/  IPA_RC_VEPA_TO_VEB_TRANSITION ; 
 scalar_t__ IS_IPA_REPLY (struct qeth_ipa_cmd*) ; 
 int /*<<< orphan*/  QETH_CARD_IFNAME (struct qeth_card*) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_issue_ipa_msg (struct qeth_ipa_cmd*,int /*<<< orphan*/ ,struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_schedule_recovery (struct qeth_card*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct qeth_card*,struct qeth_ipa_cmd*) ; 

__attribute__((used)) static struct qeth_ipa_cmd *qeth_check_ipa_data(struct qeth_card *card,
						struct qeth_ipa_cmd *cmd)
{
	QETH_CARD_TEXT(card, 5, "chkipad");

	if (IS_IPA_REPLY(cmd)) {
		if (cmd->hdr.command != IPA_CMD_SETCCID &&
		    cmd->hdr.command != IPA_CMD_DELCCID &&
		    cmd->hdr.command != IPA_CMD_MODCCID &&
		    cmd->hdr.command != IPA_CMD_SET_DIAG_ASS)
			qeth_issue_ipa_msg(cmd, cmd->hdr.return_code, card);
		return cmd;
	}

	/* handle unsolicited event: */
	switch (cmd->hdr.command) {
	case IPA_CMD_STOPLAN:
		if (cmd->hdr.return_code == IPA_RC_VEPA_TO_VEB_TRANSITION) {
			dev_err(&card->gdev->dev,
				"Interface %s is down because the adjacent port is no longer in reflective relay mode\n",
				QETH_CARD_IFNAME(card));
			schedule_work(&card->close_dev_work);
		} else {
			dev_warn(&card->gdev->dev,
				 "The link for interface %s on CHPID 0x%X failed\n",
				 QETH_CARD_IFNAME(card), card->info.chpid);
			qeth_issue_ipa_msg(cmd, cmd->hdr.return_code, card);
			netif_carrier_off(card->dev);
		}
		return NULL;
	case IPA_CMD_STARTLAN:
		dev_info(&card->gdev->dev,
			 "The link for %s on CHPID 0x%X has been restored\n",
			 QETH_CARD_IFNAME(card), card->info.chpid);
		if (card->info.hwtrap)
			card->info.hwtrap = 2;
		qeth_schedule_recovery(card);
		return NULL;
	case IPA_CMD_SETBRIDGEPORT_IQD:
	case IPA_CMD_SETBRIDGEPORT_OSA:
	case IPA_CMD_ADDRESS_CHANGE_NOTIF:
		if (card->discipline->control_event_handler(card, cmd))
			return cmd;
		return NULL;
	case IPA_CMD_MODCCID:
		return cmd;
	case IPA_CMD_REGISTER_LOCAL_ADDR:
		QETH_CARD_TEXT(card, 3, "irla");
		return NULL;
	case IPA_CMD_UNREGISTER_LOCAL_ADDR:
		QETH_CARD_TEXT(card, 3, "urla");
		return NULL;
	default:
		QETH_DBF_MESSAGE(2, "Received data is IPA but not a reply!\n");
		return cmd;
	}
}