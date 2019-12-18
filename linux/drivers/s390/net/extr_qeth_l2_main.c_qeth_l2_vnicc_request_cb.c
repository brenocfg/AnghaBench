#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct qeth_reply {scalar_t__ param; } ;
struct TYPE_20__ {int /*<<< orphan*/  timeout; } ;
struct TYPE_18__ {int /*<<< orphan*/  sup_cmds; } ;
struct TYPE_11__ {TYPE_9__ getset_timeout; TYPE_7__ query_cmds; } ;
struct TYPE_17__ {int /*<<< orphan*/  enabled; int /*<<< orphan*/  supported; } ;
struct TYPE_12__ {scalar_t__ sub_command; } ;
struct qeth_ipacmd_vnicc {TYPE_10__ data; TYPE_6__ vnicc_cmds; TYPE_1__ hdr; } ;
struct TYPE_14__ {scalar_t__ return_code; } ;
struct TYPE_13__ {struct qeth_ipacmd_vnicc vnicc; } ;
struct qeth_ipa_cmd {TYPE_3__ hdr; TYPE_2__ data; } ;
struct TYPE_15__ {int /*<<< orphan*/  cur_chars; int /*<<< orphan*/  sup_chars; } ;
struct TYPE_16__ {TYPE_4__ vnicc; } ;
struct qeth_card {TYPE_5__ options; } ;
struct TYPE_19__ {int /*<<< orphan*/ * timeout; int /*<<< orphan*/ * sup_cmds; } ;
struct _qeth_l2_vnicc_request_cbctl {TYPE_8__ result; } ;

/* Variables and functions */
 scalar_t__ IPA_VNICC_GET_TIMEOUT ; 
 scalar_t__ IPA_VNICC_QUERY_CMDS ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int qeth_l2_vnicc_makerc (struct qeth_card*,scalar_t__) ; 

__attribute__((used)) static int qeth_l2_vnicc_request_cb(struct qeth_card *card,
				    struct qeth_reply *reply,
				    unsigned long data)
{
	struct _qeth_l2_vnicc_request_cbctl *cbctl =
		(struct _qeth_l2_vnicc_request_cbctl *) reply->param;
	struct qeth_ipa_cmd *cmd = (struct qeth_ipa_cmd *) data;
	struct qeth_ipacmd_vnicc *rep = &cmd->data.vnicc;
	u32 sub_cmd = cmd->data.vnicc.hdr.sub_command;

	QETH_CARD_TEXT(card, 2, "vniccrcb");
	if (cmd->hdr.return_code)
		return qeth_l2_vnicc_makerc(card, cmd->hdr.return_code);
	/* return results to caller */
	card->options.vnicc.sup_chars = rep->vnicc_cmds.supported;
	card->options.vnicc.cur_chars = rep->vnicc_cmds.enabled;

	if (sub_cmd == IPA_VNICC_QUERY_CMDS)
		*cbctl->result.sup_cmds = rep->data.query_cmds.sup_cmds;
	else if (sub_cmd == IPA_VNICC_GET_TIMEOUT)
		*cbctl->result.timeout = rep->data.getset_timeout.timeout;

	return 0;
}