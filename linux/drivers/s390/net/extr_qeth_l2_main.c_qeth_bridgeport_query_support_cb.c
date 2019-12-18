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
struct qeth_reply {scalar_t__ param; } ;
struct TYPE_7__ {int /*<<< orphan*/  supported_cmds; } ;
struct TYPE_8__ {TYPE_2__ query_cmds_supp; } ;
struct TYPE_9__ {TYPE_3__ data; } ;
struct TYPE_10__ {TYPE_4__ sbp; } ;
struct qeth_ipa_cmd {TYPE_5__ data; } ;
struct qeth_card {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  supported; } ;
struct _qeth_sbp_cbctl {TYPE_1__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int qeth_bridgeport_makerc (struct qeth_card*,struct qeth_ipa_cmd*) ; 

__attribute__((used)) static int qeth_bridgeport_query_support_cb(struct qeth_card *card,
	struct qeth_reply *reply, unsigned long data)
{
	struct qeth_ipa_cmd *cmd = (struct qeth_ipa_cmd *) data;
	struct _qeth_sbp_cbctl *cbctl = (struct _qeth_sbp_cbctl *)reply->param;
	int rc;

	QETH_CARD_TEXT(card, 2, "brqsupcb");
	rc = qeth_bridgeport_makerc(card, cmd);
	if (rc)
		return rc;

	cbctl->data.supported =
		cmd->data.sbp.data.query_cmds_supp.supported_cmds;
	return 0;
}