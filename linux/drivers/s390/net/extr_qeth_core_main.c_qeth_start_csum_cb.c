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
typedef  int /*<<< orphan*/  u32 ;
struct qeth_reply {int /*<<< orphan*/ * param; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags_32bit; } ;
struct TYPE_5__ {TYPE_1__ data; } ;
struct TYPE_6__ {TYPE_2__ setassparms; } ;
struct qeth_ipa_cmd {TYPE_3__ data; } ;
struct qeth_card {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ qeth_setassparms_inspect_rc (struct qeth_ipa_cmd*) ; 

__attribute__((used)) static int qeth_start_csum_cb(struct qeth_card *card, struct qeth_reply *reply,
			      unsigned long data)
{
	struct qeth_ipa_cmd *cmd = (struct qeth_ipa_cmd *) data;
	u32 *features = reply->param;

	if (qeth_setassparms_inspect_rc(cmd))
		return -EIO;

	*features = cmd->data.setassparms.data.flags_32bit;
	return 0;
}