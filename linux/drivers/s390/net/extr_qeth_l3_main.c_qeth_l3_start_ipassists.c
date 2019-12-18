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
struct qeth_card {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  qeth_l3_start_ipa_arp_processing (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_l3_start_ipa_broadcast (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_l3_start_ipa_ipv6 (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_l3_start_ipa_multicast (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_l3_start_ipa_source_mac (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_l3_start_ipa_vlan (struct qeth_card*) ; 
 scalar_t__ qeth_set_access_ctrl_online (struct qeth_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qeth_l3_start_ipassists(struct qeth_card *card)
{
	QETH_CARD_TEXT(card, 3, "strtipas");

	if (qeth_set_access_ctrl_online(card, 0))
		return -EIO;
	qeth_l3_start_ipa_arp_processing(card);	/* go on*/
	qeth_l3_start_ipa_source_mac(card);	/* go on*/
	qeth_l3_start_ipa_vlan(card);		/* go on*/
	qeth_l3_start_ipa_multicast(card);		/* go on*/
	qeth_l3_start_ipa_ipv6(card);		/* go on*/
	qeth_l3_start_ipa_broadcast(card);		/* go on*/
	return 0;
}