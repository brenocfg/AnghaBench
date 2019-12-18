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
struct qeth_tso_start_data {int /*<<< orphan*/  supported; int /*<<< orphan*/  mss; } ;
struct qeth_reply {struct qeth_tso_start_data* param; } ;
struct TYPE_8__ {int /*<<< orphan*/  supported; int /*<<< orphan*/  mss; } ;
struct TYPE_5__ {TYPE_4__ tso; } ;
struct TYPE_6__ {TYPE_1__ data; } ;
struct TYPE_7__ {TYPE_2__ setassparms; } ;
struct qeth_ipa_cmd {TYPE_3__ data; } ;
struct qeth_card {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ qeth_setassparms_inspect_rc (struct qeth_ipa_cmd*) ; 

__attribute__((used)) static int qeth_start_tso_cb(struct qeth_card *card, struct qeth_reply *reply,
			     unsigned long data)
{
	struct qeth_ipa_cmd *cmd = (struct qeth_ipa_cmd *) data;
	struct qeth_tso_start_data *tso_data = reply->param;

	if (qeth_setassparms_inspect_rc(cmd))
		return -EIO;

	tso_data->mss = cmd->data.setassparms.data.tso.mss;
	tso_data->supported = cmd->data.setassparms.data.tso.supported;
	return 0;
}