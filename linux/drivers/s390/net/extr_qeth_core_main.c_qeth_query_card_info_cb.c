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
struct qeth_reply {scalar_t__ param; } ;
struct qeth_query_card_info {int /*<<< orphan*/  port_speed; int /*<<< orphan*/  port_mode; int /*<<< orphan*/  card_type; } ;
struct TYPE_4__ {struct qeth_query_card_info card_info; } ;
struct TYPE_5__ {TYPE_1__ data; } ;
struct TYPE_6__ {TYPE_2__ setadapterparms; } ;
struct qeth_ipa_cmd {TYPE_3__ data; } ;
struct qeth_card {int dummy; } ;
struct carrier_info {int /*<<< orphan*/  port_speed; int /*<<< orphan*/  port_mode; int /*<<< orphan*/  card_type; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 scalar_t__ qeth_setadpparms_inspect_rc (struct qeth_ipa_cmd*) ; 

__attribute__((used)) static int qeth_query_card_info_cb(struct qeth_card *card,
				   struct qeth_reply *reply, unsigned long data)
{
	struct carrier_info *carrier_info = (struct carrier_info *)reply->param;
	struct qeth_ipa_cmd *cmd = (struct qeth_ipa_cmd *)data;
	struct qeth_query_card_info *card_info;

	QETH_CARD_TEXT(card, 2, "qcrdincb");
	if (qeth_setadpparms_inspect_rc(cmd))
		return -EIO;

	card_info = &cmd->data.setadapterparms.data.card_info;
	carrier_info->card_type = card_info->card_type;
	carrier_info->port_mode = card_info->port_mode;
	carrier_info->port_speed = card_info->port_speed;
	return 0;
}