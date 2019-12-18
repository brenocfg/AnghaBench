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
typedef  int /*<<< orphan*/  u32 ;
struct qeth_cmd_buffer {int dummy; } ;
struct qeth_card {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  vnic_char; } ;
struct TYPE_7__ {TYPE_1__ set_char; } ;
struct TYPE_8__ {TYPE_2__ data; } ;
struct TYPE_9__ {TYPE_3__ vnicc; } ;
struct TYPE_10__ {TYPE_4__ data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  VNICC_DATA_SIZEOF (int /*<<< orphan*/ ) ; 
 TYPE_5__* __ipa_cmd (struct qeth_cmd_buffer*) ; 
 struct qeth_cmd_buffer* qeth_l2_vnicc_build_cmd (struct qeth_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_l2_vnicc_request_cb ; 
 int qeth_send_ipa_cmd (struct qeth_card*,struct qeth_cmd_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_char ; 

__attribute__((used)) static int qeth_l2_vnicc_set_char(struct qeth_card *card, u32 vnic_char,
				      u32 cmd)
{
	struct qeth_cmd_buffer *iob;

	QETH_CARD_TEXT(card, 2, "vniccedc");
	iob = qeth_l2_vnicc_build_cmd(card, cmd, VNICC_DATA_SIZEOF(set_char));
	if (!iob)
		return -ENOMEM;

	__ipa_cmd(iob)->data.vnicc.data.set_char.vnic_char = vnic_char;

	return qeth_send_ipa_cmd(card, iob, qeth_l2_vnicc_request_cb, NULL);
}