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
typedef  int u32 ;
struct qeth_card {TYPE_1__* gdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPA_CMD_ASS_START ; 
 int /*<<< orphan*/  IPA_IPV6 ; 
 int /*<<< orphan*/  IPA_PASSTHRU ; 
 scalar_t__ IS_IQD (struct qeth_card*) ; 
 int /*<<< orphan*/  QETH_CARD_IFNAME (struct qeth_card*) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int qeth_send_simple_setassparms (struct qeth_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int qeth_send_simple_setassparms_v6 (struct qeth_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qeth_l3_softsetup_ipv6(struct qeth_card *card)
{
	u32 ipv6_data = 3;
	int rc;

	QETH_CARD_TEXT(card, 3, "softipv6");

	if (IS_IQD(card))
		goto out;

	rc = qeth_send_simple_setassparms(card, IPA_IPV6, IPA_CMD_ASS_START,
					  &ipv6_data);
	if (rc) {
		dev_err(&card->gdev->dev,
			"Activating IPv6 support for %s failed\n",
			QETH_CARD_IFNAME(card));
		return rc;
	}
	rc = qeth_send_simple_setassparms_v6(card, IPA_IPV6, IPA_CMD_ASS_START,
					     NULL);
	if (rc) {
		dev_err(&card->gdev->dev,
			"Activating IPv6 support for %s failed\n",
			 QETH_CARD_IFNAME(card));
		return rc;
	}
	rc = qeth_send_simple_setassparms_v6(card, IPA_PASSTHRU,
					     IPA_CMD_ASS_START, NULL);
	if (rc) {
		dev_warn(&card->gdev->dev,
			"Enabling the passthrough mode for %s failed\n",
			QETH_CARD_IFNAME(card));
		return rc;
	}
out:
	dev_info(&card->gdev->dev, "IPV6 enabled\n");
	return 0;
}