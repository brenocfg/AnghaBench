#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct qeth_switch_info {int dummy; } ;
struct qeth_cmd_buffer {int dummy; } ;
struct qeth_card {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEDIUM ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IPA_SETADP_QUERY_SWITCH_ATTRIBUTES ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_adp_supported (struct qeth_card*,int /*<<< orphan*/ ) ; 
 struct qeth_cmd_buffer* qeth_get_adapter_cmd (struct qeth_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_query_switch_attributes_cb ; 
 int qeth_send_ipa_cmd (struct qeth_card*,struct qeth_cmd_buffer*,int /*<<< orphan*/ ,struct qeth_switch_info*) ; 

int qeth_query_switch_attributes(struct qeth_card *card,
				 struct qeth_switch_info *sw_info)
{
	struct qeth_cmd_buffer *iob;

	QETH_CARD_TEXT(card, 2, "qswiattr");
	if (!qeth_adp_supported(card, IPA_SETADP_QUERY_SWITCH_ATTRIBUTES))
		return -EOPNOTSUPP;
	if (!netif_carrier_ok(card->dev))
		return -ENOMEDIUM;
	iob = qeth_get_adapter_cmd(card, IPA_SETADP_QUERY_SWITCH_ATTRIBUTES, 0);
	if (!iob)
		return -ENOMEM;
	return qeth_send_ipa_cmd(card, iob,
				qeth_query_switch_attributes_cb, sw_info);
}