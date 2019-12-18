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
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct TYPE_3__ {TYPE_2__ route6; } ;
struct qeth_card {TYPE_1__ options; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_DEVID (struct qeth_card*) ; 
 int /*<<< orphan*/  IPA_IPV6 ; 
 int /*<<< orphan*/  NO_ROUTER ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_PROT_IPV6 ; 
 int /*<<< orphan*/  qeth_is_supported (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int qeth_l3_correct_routing_type (struct qeth_card*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int qeth_l3_send_setrouting (struct qeth_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int qeth_l3_setrouting_v6(struct qeth_card *card)
{
	int rc = 0;

	QETH_CARD_TEXT(card, 3, "setrtg6");

	if (!qeth_is_supported(card, IPA_IPV6))
		return 0;
	rc = qeth_l3_correct_routing_type(card, &card->options.route6.type,
				  QETH_PROT_IPV6);
	if (rc)
		return rc;

	rc = qeth_l3_send_setrouting(card, card->options.route6.type,
				  QETH_PROT_IPV6);
	if (rc) {
		card->options.route6.type = NO_ROUTER;
		QETH_DBF_MESSAGE(2, "Error (%#06x) while setting routing type on device %x. Type set to 'no router'.\n",
				 rc, CARD_DEVID(card));
	}
	return rc;
}