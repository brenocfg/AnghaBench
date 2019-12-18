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
struct qeth_reply {int dummy; } ;
struct TYPE_9__ {int action; } ;
struct TYPE_10__ {TYPE_4__ diagass; } ;
struct TYPE_6__ {scalar_t__ return_code; } ;
struct qeth_ipa_cmd {TYPE_5__ data; TYPE_1__ hdr; } ;
struct TYPE_7__ {int /*<<< orphan*/  promisc_mode; } ;
struct qeth_card {TYPE_3__* gdev; TYPE_2__ info; } ;
typedef  scalar_t__ __u16 ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_DEVID (struct qeth_card*) ; 
 int EIO ; 
#define  IPA_RC_HARDWARE_AUTH_ERROR 133 
#define  IPA_RC_INVALID_SUBCMD 132 
#define  IPA_RC_TRACE_ALREADY_ACTIVE 131 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT_ (struct qeth_card*,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int,int /*<<< orphan*/ ) ; 
#define  QETH_DIAGS_CMD_TRACE_DISABLE 130 
#define  QETH_DIAGS_CMD_TRACE_ENABLE 129 
#define  QETH_DIAGS_CMD_TRACE_QUERY 128 
 int /*<<< orphan*/  SET_PROMISC_MODE_OFF ; 
 int /*<<< orphan*/  SET_PROMISC_MODE_ON ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
qeth_diags_trace_cb(struct qeth_card *card, struct qeth_reply *reply,
			    unsigned long data)
{
	struct qeth_ipa_cmd	   *cmd;
	__u16 rc;

	QETH_CARD_TEXT(card, 2, "diastrcb");

	cmd = (struct qeth_ipa_cmd *)data;
	rc = cmd->hdr.return_code;
	if (rc)
		QETH_CARD_TEXT_(card, 2, "dxter%x", rc);
	switch (cmd->data.diagass.action) {
	case QETH_DIAGS_CMD_TRACE_QUERY:
		break;
	case QETH_DIAGS_CMD_TRACE_DISABLE:
		switch (rc) {
		case 0:
		case IPA_RC_INVALID_SUBCMD:
			card->info.promisc_mode = SET_PROMISC_MODE_OFF;
			dev_info(&card->gdev->dev, "The HiperSockets network "
				"traffic analyzer is deactivated\n");
			break;
		default:
			break;
		}
		break;
	case QETH_DIAGS_CMD_TRACE_ENABLE:
		switch (rc) {
		case 0:
			card->info.promisc_mode = SET_PROMISC_MODE_ON;
			dev_info(&card->gdev->dev, "The HiperSockets network "
				"traffic analyzer is activated\n");
			break;
		case IPA_RC_HARDWARE_AUTH_ERROR:
			dev_warn(&card->gdev->dev, "The device is not "
				"authorized to run as a HiperSockets network "
				"traffic analyzer\n");
			break;
		case IPA_RC_TRACE_ALREADY_ACTIVE:
			dev_warn(&card->gdev->dev, "A HiperSockets "
				"network traffic analyzer is already "
				"active in the HiperSockets LAN\n");
			break;
		default:
			break;
		}
		break;
	default:
		QETH_DBF_MESSAGE(2, "Unknown sniffer action (%#06x) on device %x\n",
				 cmd->data.diagass.action, CARD_DEVID(card));
	}

	return rc ? -EIO : 0;
}