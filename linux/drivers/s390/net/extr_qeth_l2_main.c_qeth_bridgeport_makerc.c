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
typedef  int u16 ;
struct TYPE_7__ {int command_code; int return_code; } ;
struct qeth_ipacmd_setbridgeport {TYPE_3__ hdr; } ;
struct TYPE_6__ {int return_code; } ;
struct TYPE_5__ {struct qeth_ipacmd_setbridgeport sbp; } ;
struct qeth_ipa_cmd {TYPE_2__ hdr; TYPE_1__ data; } ;
struct qeth_card {TYPE_4__* gdev; } ;
typedef  enum qeth_ipa_sbp_cmd { ____Placeholder_qeth_ipa_sbp_cmd } qeth_ipa_sbp_cmd ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EACCES ; 
 int EBUSY ; 
 int EEXIST ; 
 int EIO ; 
 int ENODEV ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
#define  IPA_RC_L2_UNSUPPORTED_CMD 147 
#define  IPA_RC_NOTSUPP 146 
#define  IPA_RC_SBP_IQD_ANO_DEV_PRIMARY 145 
#define  IPA_RC_SBP_IQD_CURRENT_PRIMARY 144 
#define  IPA_RC_SBP_IQD_CURRENT_SECOND 143 
#define  IPA_RC_SBP_IQD_LIMIT_SECOND 142 
#define  IPA_RC_SBP_IQD_NOT_AUTHD_BY_ZMAN 141 
#define  IPA_RC_SBP_IQD_NOT_CONFIGURED 140 
#define  IPA_RC_SBP_IQD_OS_MISMATCH 139 
#define  IPA_RC_SBP_OSA_ANO_DEV_PRIMARY 138 
#define  IPA_RC_SBP_OSA_CURRENT_PRIMARY 137 
#define  IPA_RC_SBP_OSA_CURRENT_SECOND 136 
#define  IPA_RC_SBP_OSA_LIMIT_SECOND 135 
#define  IPA_RC_SBP_OSA_NOT_AUTHD_BY_ZMAN 134 
#define  IPA_RC_SBP_OSA_NOT_CONFIGURED 133 
#define  IPA_RC_SBP_OSA_OS_MISMATCH 132 
#define  IPA_RC_SUCCESS 131 
#define  IPA_RC_UNSUPPORTED_COMMAND 130 
#define  IPA_SBP_SET_PRIMARY_BRIDGE_PORT 129 
#define  IPA_SBP_SET_SECONDARY_BRIDGE_PORT 128 
 scalar_t__ IS_IQD (struct qeth_card*) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT_ (struct qeth_card*,int,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int qeth_bridgeport_makerc(struct qeth_card *card,
				  struct qeth_ipa_cmd *cmd)
{
	struct qeth_ipacmd_setbridgeport *sbp = &cmd->data.sbp;
	enum qeth_ipa_sbp_cmd setcmd = sbp->hdr.command_code;
	u16 ipa_rc = cmd->hdr.return_code;
	u16 sbp_rc = sbp->hdr.return_code;
	int rc;

	if (ipa_rc == IPA_RC_SUCCESS && sbp_rc == IPA_RC_SUCCESS)
		return 0;

	if ((IS_IQD(card) && ipa_rc == IPA_RC_SUCCESS) ||
	    (!IS_IQD(card) && ipa_rc == sbp_rc)) {
		switch (sbp_rc) {
		case IPA_RC_SUCCESS:
			rc = 0;
			break;
		case IPA_RC_L2_UNSUPPORTED_CMD:
		case IPA_RC_UNSUPPORTED_COMMAND:
			rc = -EOPNOTSUPP;
			break;
		case IPA_RC_SBP_OSA_NOT_CONFIGURED:
		case IPA_RC_SBP_IQD_NOT_CONFIGURED:
			rc = -ENODEV; /* maybe not the best code here? */
			dev_err(&card->gdev->dev,
	"The device is not configured as a Bridge Port\n");
			break;
		case IPA_RC_SBP_OSA_OS_MISMATCH:
		case IPA_RC_SBP_IQD_OS_MISMATCH:
			rc = -EPERM;
			dev_err(&card->gdev->dev,
	"A Bridge Port is already configured by a different operating system\n");
			break;
		case IPA_RC_SBP_OSA_ANO_DEV_PRIMARY:
		case IPA_RC_SBP_IQD_ANO_DEV_PRIMARY:
			switch (setcmd) {
			case IPA_SBP_SET_PRIMARY_BRIDGE_PORT:
				rc = -EEXIST;
				dev_err(&card->gdev->dev,
	"The LAN already has a primary Bridge Port\n");
				break;
			case IPA_SBP_SET_SECONDARY_BRIDGE_PORT:
				rc = -EBUSY;
				dev_err(&card->gdev->dev,
	"The device is already a primary Bridge Port\n");
				break;
			default:
				rc = -EIO;
			}
			break;
		case IPA_RC_SBP_OSA_CURRENT_SECOND:
		case IPA_RC_SBP_IQD_CURRENT_SECOND:
			rc = -EBUSY;
			dev_err(&card->gdev->dev,
	"The device is already a secondary Bridge Port\n");
			break;
		case IPA_RC_SBP_OSA_LIMIT_SECOND:
		case IPA_RC_SBP_IQD_LIMIT_SECOND:
			rc = -EEXIST;
			dev_err(&card->gdev->dev,
	"The LAN cannot have more secondary Bridge Ports\n");
			break;
		case IPA_RC_SBP_OSA_CURRENT_PRIMARY:
		case IPA_RC_SBP_IQD_CURRENT_PRIMARY:
			rc = -EBUSY;
			dev_err(&card->gdev->dev,
	"The device is already a primary Bridge Port\n");
			break;
		case IPA_RC_SBP_OSA_NOT_AUTHD_BY_ZMAN:
		case IPA_RC_SBP_IQD_NOT_AUTHD_BY_ZMAN:
			rc = -EACCES;
			dev_err(&card->gdev->dev,
	"The device is not authorized to be a Bridge Port\n");
			break;
		default:
			rc = -EIO;
		}
	} else {
		switch (ipa_rc) {
		case IPA_RC_NOTSUPP:
			rc = -EOPNOTSUPP;
			break;
		case IPA_RC_UNSUPPORTED_COMMAND:
			rc = -EOPNOTSUPP;
			break;
		default:
			rc = -EIO;
		}
	}

	if (rc) {
		QETH_CARD_TEXT_(card, 2, "SBPi%04x", ipa_rc);
		QETH_CARD_TEXT_(card, 2, "SBPc%04x", sbp_rc);
	}
	return rc;
}