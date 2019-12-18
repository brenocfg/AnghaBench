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
struct qeth_reply {int dummy; } ;
struct TYPE_6__ {scalar_t__ return_code; int /*<<< orphan*/  command; } ;
struct TYPE_4__ {int /*<<< orphan*/  vlan_id; } ;
struct TYPE_5__ {TYPE_1__ setdelvlan; } ;
struct qeth_ipa_cmd {TYPE_3__ hdr; TYPE_2__ data; } ;
struct qeth_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_DEVID (struct qeth_card*) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT_ (struct qeth_card*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int qeth_l2_setdelvlan_makerc (struct qeth_card*,scalar_t__) ; 

__attribute__((used)) static int qeth_l2_send_setdelvlan_cb(struct qeth_card *card,
				      struct qeth_reply *reply,
				      unsigned long data)
{
	struct qeth_ipa_cmd *cmd = (struct qeth_ipa_cmd *) data;

	QETH_CARD_TEXT(card, 2, "L2sdvcb");
	if (cmd->hdr.return_code) {
		QETH_DBF_MESSAGE(2, "Error in processing VLAN %u on device %x: %#x.\n",
				 cmd->data.setdelvlan.vlan_id,
				 CARD_DEVID(card), cmd->hdr.return_code);
		QETH_CARD_TEXT_(card, 2, "L2VL%4x", cmd->hdr.command);
	}
	return qeth_l2_setdelvlan_makerc(card, cmd->hdr.return_code);
}