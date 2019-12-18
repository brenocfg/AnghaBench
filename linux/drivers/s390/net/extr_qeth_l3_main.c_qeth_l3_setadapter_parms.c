#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qeth_card {TYPE_1__* gdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPA_SETADP_ALTER_MAC_ADDRESS ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ qeth_adp_supported (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int qeth_setadpparms_change_macaddr (struct qeth_card*) ; 

__attribute__((used)) static int qeth_l3_setadapter_parms(struct qeth_card *card)
{
	int rc = 0;

	QETH_CARD_TEXT(card, 2, "setadprm");

	if (qeth_adp_supported(card, IPA_SETADP_ALTER_MAC_ADDRESS)) {
		rc = qeth_setadpparms_change_macaddr(card);
		if (rc)
			dev_warn(&card->gdev->dev, "Reading the adapter MAC"
				" address failed\n");
	}

	return rc;
}