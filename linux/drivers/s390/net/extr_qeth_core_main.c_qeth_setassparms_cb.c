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
struct qeth_reply {int dummy; } ;
struct TYPE_14__ {scalar_t__ prot_version; int /*<<< orphan*/  ipa_enabled; scalar_t__ return_code; } ;
struct TYPE_8__ {scalar_t__ return_code; } ;
struct TYPE_9__ {TYPE_1__ hdr; } ;
struct TYPE_10__ {TYPE_2__ setassparms; } ;
struct qeth_ipa_cmd {TYPE_7__ hdr; TYPE_3__ data; } ;
struct TYPE_12__ {int /*<<< orphan*/  enabled_funcs; } ;
struct TYPE_11__ {int /*<<< orphan*/  enabled_funcs; } ;
struct TYPE_13__ {TYPE_5__ ipa6; TYPE_4__ ipa4; } ;
struct qeth_card {TYPE_6__ options; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 scalar_t__ QETH_PROT_IPV4 ; 
 scalar_t__ QETH_PROT_IPV6 ; 

int qeth_setassparms_cb(struct qeth_card *card,
			struct qeth_reply *reply, unsigned long data)
{
	struct qeth_ipa_cmd *cmd = (struct qeth_ipa_cmd *) data;

	QETH_CARD_TEXT(card, 4, "defadpcb");

	if (cmd->hdr.return_code)
		return -EIO;

	cmd->hdr.return_code = cmd->data.setassparms.hdr.return_code;
	if (cmd->hdr.prot_version == QETH_PROT_IPV4)
		card->options.ipa4.enabled_funcs = cmd->hdr.ipa_enabled;
	if (cmd->hdr.prot_version == QETH_PROT_IPV6)
		card->options.ipa6.enabled_funcs = cmd->hdr.ipa_enabled;
	return 0;
}