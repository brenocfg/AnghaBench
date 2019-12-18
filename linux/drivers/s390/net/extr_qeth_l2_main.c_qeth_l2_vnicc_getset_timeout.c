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
typedef  scalar_t__ u32 ;
struct qeth_vnicc_getset_timeout {scalar_t__ timeout; scalar_t__ vnic_char; } ;
struct qeth_cmd_buffer {int dummy; } ;
struct qeth_card {int dummy; } ;
struct TYPE_6__ {scalar_t__* timeout; } ;
struct _qeth_l2_vnicc_request_cbctl {TYPE_1__ result; } ;
struct TYPE_8__ {struct qeth_vnicc_getset_timeout getset_timeout; } ;
struct TYPE_7__ {TYPE_3__ data; } ;
struct TYPE_9__ {TYPE_2__ vnicc; } ;
struct TYPE_10__ {TYPE_4__ data; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IPA_VNICC_GET_TIMEOUT ; 
 scalar_t__ IPA_VNICC_SET_TIMEOUT ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  VNICC_DATA_SIZEOF (struct qeth_vnicc_getset_timeout*) ; 
 TYPE_5__* __ipa_cmd (struct qeth_cmd_buffer*) ; 
 struct qeth_cmd_buffer* qeth_l2_vnicc_build_cmd (struct qeth_card*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_l2_vnicc_request_cb ; 
 int qeth_send_ipa_cmd (struct qeth_card*,struct qeth_cmd_buffer*,int /*<<< orphan*/ ,struct _qeth_l2_vnicc_request_cbctl*) ; 

__attribute__((used)) static int qeth_l2_vnicc_getset_timeout(struct qeth_card *card, u32 vnicc,
					u32 cmd, u32 *timeout)
{
	struct qeth_vnicc_getset_timeout *getset_timeout;
	struct _qeth_l2_vnicc_request_cbctl cbctl;
	struct qeth_cmd_buffer *iob;

	QETH_CARD_TEXT(card, 2, "vniccgst");
	iob = qeth_l2_vnicc_build_cmd(card, cmd,
				      VNICC_DATA_SIZEOF(getset_timeout));
	if (!iob)
		return -ENOMEM;

	getset_timeout = &__ipa_cmd(iob)->data.vnicc.data.getset_timeout;
	getset_timeout->vnic_char = vnicc;

	if (cmd == IPA_VNICC_SET_TIMEOUT)
		getset_timeout->timeout = *timeout;

	/* prepare callback control */
	if (cmd == IPA_VNICC_GET_TIMEOUT)
		cbctl.result.timeout = timeout;

	return qeth_send_ipa_cmd(card, iob, qeth_l2_vnicc_request_cb, &cbctl);
}