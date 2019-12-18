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
struct qeth_set_access_ctrl {int subcmd_code; } ;
struct TYPE_4__ {struct qeth_set_access_ctrl set_access_ctrl; } ;
struct TYPE_6__ {TYPE_1__ data; } ;
struct TYPE_5__ {TYPE_3__ setadapterparms; } ;
struct qeth_ipa_cmd {TYPE_2__ data; } ;
struct qeth_cmd_buffer {int dummy; } ;
struct qeth_card {int dummy; } ;
typedef  enum qeth_ipa_isolation_modes { ____Placeholder_qeth_ipa_isolation_modes } qeth_ipa_isolation_modes ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IPA_SETADP_SET_ACCESS_CONTROL ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT_ (struct qeth_card*,int,char*,int) ; 
 int /*<<< orphan*/  SETADP_DATA_SIZEOF (int /*<<< orphan*/ ) ; 
 struct qeth_ipa_cmd* __ipa_cmd (struct qeth_cmd_buffer*) ; 
 struct qeth_cmd_buffer* qeth_get_adapter_cmd (struct qeth_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qeth_send_ipa_cmd (struct qeth_card*,struct qeth_cmd_buffer*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  qeth_setadpparms_set_access_ctrl_cb ; 
 int /*<<< orphan*/  set_access_ctrl ; 

__attribute__((used)) static int qeth_setadpparms_set_access_ctrl(struct qeth_card *card,
		enum qeth_ipa_isolation_modes isolation, int fallback)
{
	int rc;
	struct qeth_cmd_buffer *iob;
	struct qeth_ipa_cmd *cmd;
	struct qeth_set_access_ctrl *access_ctrl_req;

	QETH_CARD_TEXT(card, 4, "setacctl");

	iob = qeth_get_adapter_cmd(card, IPA_SETADP_SET_ACCESS_CONTROL,
				   SETADP_DATA_SIZEOF(set_access_ctrl));
	if (!iob)
		return -ENOMEM;
	cmd = __ipa_cmd(iob);
	access_ctrl_req = &cmd->data.setadapterparms.data.set_access_ctrl;
	access_ctrl_req->subcmd_code = isolation;

	rc = qeth_send_ipa_cmd(card, iob, qeth_setadpparms_set_access_ctrl_cb,
			       &fallback);
	QETH_CARD_TEXT_(card, 2, "rc=%d", rc);
	return rc;
}