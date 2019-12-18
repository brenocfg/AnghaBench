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
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IPA_CMD_ASS_START ; 
 int /*<<< orphan*/  IPA_FULL_VLAN ; 
 int /*<<< orphan*/  IPA_VLAN_PRIO ; 
 int /*<<< orphan*/  QETH_CARD_IFNAME (struct qeth_card*) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_is_supported (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int qeth_send_simple_setassparms (struct qeth_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qeth_l3_start_ipa_vlan(struct qeth_card *card)
{
	int rc = 0;

	QETH_CARD_TEXT(card, 3, "strtvlan");

	if (!qeth_is_supported(card, IPA_FULL_VLAN)) {
		dev_info(&card->gdev->dev,
			"VLAN not supported on %s\n", QETH_CARD_IFNAME(card));
		return -EOPNOTSUPP;
	}

	rc = qeth_send_simple_setassparms(card, IPA_VLAN_PRIO,
					  IPA_CMD_ASS_START, NULL);
	if (rc) {
		dev_warn(&card->gdev->dev,
			"Starting VLAN support for %s failed\n",
			QETH_CARD_IFNAME(card));
	} else {
		dev_info(&card->gdev->dev, "VLAN enabled\n");
	}
	return rc;
}