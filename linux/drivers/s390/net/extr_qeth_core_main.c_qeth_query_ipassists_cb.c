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
struct qeth_reply {int dummy; } ;
struct TYPE_8__ {int return_code; scalar_t__ prot_version; int /*<<< orphan*/  ipa_enabled; int /*<<< orphan*/  ipa_supported; } ;
struct qeth_ipa_cmd {TYPE_4__ hdr; } ;
struct TYPE_6__ {int /*<<< orphan*/  enabled_funcs; int /*<<< orphan*/  supported_funcs; } ;
struct TYPE_5__ {int /*<<< orphan*/  enabled_funcs; int /*<<< orphan*/  supported_funcs; } ;
struct TYPE_7__ {TYPE_2__ ipa6; TYPE_1__ ipa4; } ;
struct qeth_card {TYPE_3__ options; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_DEVID (struct qeth_card*) ; 
 int EIO ; 
 int EOPNOTSUPP ; 
#define  IPA_RC_L2_UNSUPPORTED_CMD 130 
#define  IPA_RC_NOTSUPP 129 
#define  IPA_RC_SUCCESS 128 
 int /*<<< orphan*/  IPA_SETADAPTERPARMS ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ QETH_PROT_IPV4 ; 
 scalar_t__ QETH_PROT_IPV6 ; 

__attribute__((used)) static int qeth_query_ipassists_cb(struct qeth_card *card,
		struct qeth_reply *reply, unsigned long data)
{
	struct qeth_ipa_cmd *cmd;

	QETH_CARD_TEXT(card, 2, "qipasscb");

	cmd = (struct qeth_ipa_cmd *) data;

	switch (cmd->hdr.return_code) {
	case IPA_RC_SUCCESS:
		break;
	case IPA_RC_NOTSUPP:
	case IPA_RC_L2_UNSUPPORTED_CMD:
		QETH_CARD_TEXT(card, 2, "ipaunsup");
		card->options.ipa4.supported_funcs |= IPA_SETADAPTERPARMS;
		card->options.ipa6.supported_funcs |= IPA_SETADAPTERPARMS;
		return -EOPNOTSUPP;
	default:
		QETH_DBF_MESSAGE(1, "IPA_CMD_QIPASSIST on device %x: Unhandled rc=%#x\n",
				 CARD_DEVID(card), cmd->hdr.return_code);
		return -EIO;
	}

	if (cmd->hdr.prot_version == QETH_PROT_IPV4) {
		card->options.ipa4.supported_funcs = cmd->hdr.ipa_supported;
		card->options.ipa4.enabled_funcs = cmd->hdr.ipa_enabled;
	} else if (cmd->hdr.prot_version == QETH_PROT_IPV6) {
		card->options.ipa6.supported_funcs = cmd->hdr.ipa_supported;
		card->options.ipa6.enabled_funcs = cmd->hdr.ipa_enabled;
	} else
		QETH_DBF_MESSAGE(1, "IPA_CMD_QIPASSIST on device %x: Flawed LIC detected\n",
				 CARD_DEVID(card));
	return 0;
}