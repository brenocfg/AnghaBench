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
 int /*<<< orphan*/  IPA_SOURCE_MAC ; 
 int /*<<< orphan*/  QETH_CARD_IFNAME (struct qeth_card*) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_is_supported (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int qeth_send_simple_setassparms (struct qeth_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qeth_l3_start_ipa_source_mac(struct qeth_card *card)
{
	int rc;

	QETH_CARD_TEXT(card, 3, "stsrcmac");

	if (!qeth_is_supported(card, IPA_SOURCE_MAC)) {
		dev_info(&card->gdev->dev,
			"Inbound source MAC-address not supported on %s\n",
			QETH_CARD_IFNAME(card));
		return -EOPNOTSUPP;
	}

	rc = qeth_send_simple_setassparms(card, IPA_SOURCE_MAC,
					  IPA_CMD_ASS_START, NULL);
	if (rc)
		dev_warn(&card->gdev->dev,
			"Starting source MAC-address support for %s failed\n",
			QETH_CARD_IFNAME(card));
	return rc;
}