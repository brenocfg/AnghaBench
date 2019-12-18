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
struct qeth_reply {int dummy; } ;
struct qeth_ipa_cmd {int dummy; } ;
struct qeth_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int qeth_bridgeport_makerc (struct qeth_card*,struct qeth_ipa_cmd*) ; 

__attribute__((used)) static int qeth_bridgeport_set_cb(struct qeth_card *card,
	struct qeth_reply *reply, unsigned long data)
{
	struct qeth_ipa_cmd *cmd = (struct qeth_ipa_cmd *)data;

	QETH_CARD_TEXT(card, 2, "brsetrcb");
	return qeth_bridgeport_makerc(card, cmd);
}