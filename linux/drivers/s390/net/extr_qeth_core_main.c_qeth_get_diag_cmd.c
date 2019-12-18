#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qeth_ipacmd_diagass {int subcmd; scalar_t__ subcmd_len; } ;
struct qeth_cmd_buffer {int dummy; } ;
struct qeth_card {int dummy; } ;
typedef  enum qeth_diags_cmds { ____Placeholder_qeth_diags_cmds } qeth_diags_cmds ;
struct TYPE_3__ {struct qeth_ipacmd_diagass diagass; } ;
struct TYPE_4__ {TYPE_1__ data; } ;

/* Variables and functions */
 scalar_t__ DIAG_HDR_LEN ; 
 scalar_t__ DIAG_SUB_HDR_LEN ; 
 int /*<<< orphan*/  IPA_CMD_SET_DIAG_ASS ; 
 int /*<<< orphan*/  QETH_PROT_NONE ; 
 TYPE_2__* __ipa_cmd (struct qeth_cmd_buffer*) ; 
 struct qeth_cmd_buffer* qeth_ipa_alloc_cmd (struct qeth_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

struct qeth_cmd_buffer *qeth_get_diag_cmd(struct qeth_card *card,
					  enum qeth_diags_cmds sub_cmd,
					  unsigned int data_length)
{
	struct qeth_ipacmd_diagass *cmd;
	struct qeth_cmd_buffer *iob;

	iob = qeth_ipa_alloc_cmd(card, IPA_CMD_SET_DIAG_ASS, QETH_PROT_NONE,
				 DIAG_HDR_LEN + data_length);
	if (!iob)
		return NULL;

	cmd = &__ipa_cmd(iob)->data.diagass;
	cmd->subcmd_len = DIAG_SUB_HDR_LEN + data_length;
	cmd->subcmd = sub_cmd;
	return iob;
}