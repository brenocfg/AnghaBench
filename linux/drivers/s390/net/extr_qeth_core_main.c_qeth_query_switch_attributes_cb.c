#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qeth_switch_info {int /*<<< orphan*/  settings; int /*<<< orphan*/  capabilities; } ;
struct qeth_reply {scalar_t__ param; } ;
struct qeth_query_switch_attributes {int /*<<< orphan*/  settings; int /*<<< orphan*/  capabilities; } ;
struct TYPE_4__ {struct qeth_query_switch_attributes query_switch_attributes; } ;
struct TYPE_5__ {TYPE_1__ data; } ;
struct TYPE_6__ {TYPE_2__ setadapterparms; } ;
struct qeth_ipa_cmd {TYPE_3__ data; } ;
struct qeth_card {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT_ (struct qeth_card*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ qeth_setadpparms_inspect_rc (struct qeth_ipa_cmd*) ; 

__attribute__((used)) static int qeth_query_switch_attributes_cb(struct qeth_card *card,
				struct qeth_reply *reply, unsigned long data)
{
	struct qeth_ipa_cmd *cmd = (struct qeth_ipa_cmd *) data;
	struct qeth_query_switch_attributes *attrs;
	struct qeth_switch_info *sw_info;

	QETH_CARD_TEXT(card, 2, "qswiatcb");
	if (qeth_setadpparms_inspect_rc(cmd))
		return -EIO;

	sw_info = (struct qeth_switch_info *)reply->param;
	attrs = &cmd->data.setadapterparms.data.query_switch_attributes;
	sw_info->capabilities = attrs->capabilities;
	sw_info->settings = attrs->settings;
	QETH_CARD_TEXT_(card, 2, "%04x%04x", sw_info->capabilities,
			sw_info->settings);
	return 0;
}