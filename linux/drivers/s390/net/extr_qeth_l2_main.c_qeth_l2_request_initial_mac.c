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
struct qeth_card {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_DEVID (struct qeth_card*) ; 
 int EADDRNOTAVAIL ; 
 scalar_t__ IS_OSM (struct qeth_card*) ; 
 int /*<<< orphan*/  IS_OSN (struct qeth_card*) ; 
 scalar_t__ IS_OSX (struct qeth_card*) ; 
 scalar_t__ MACHINE_IS_VM ; 
 int /*<<< orphan*/  QETH_CARD_HEX (struct qeth_card*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT_ (struct qeth_card*,int,char*,int) ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  eth_hw_addr_random (TYPE_1__*) ; 
 int qeth_setadpparms_change_macaddr (struct qeth_card*) ; 
 int qeth_vm_request_mac (struct qeth_card*) ; 

__attribute__((used)) static int qeth_l2_request_initial_mac(struct qeth_card *card)
{
	int rc = 0;

	QETH_CARD_TEXT(card, 2, "l2reqmac");

	if (MACHINE_IS_VM) {
		rc = qeth_vm_request_mac(card);
		if (!rc)
			goto out;
		QETH_DBF_MESSAGE(2, "z/VM MAC Service failed on device %x: %#x\n",
				 CARD_DEVID(card), rc);
		QETH_CARD_TEXT_(card, 2, "err%04x", rc);
		/* fall back to alternative mechanism: */
	}

	if (!IS_OSN(card)) {
		rc = qeth_setadpparms_change_macaddr(card);
		if (!rc)
			goto out;
		QETH_DBF_MESSAGE(2, "READ_MAC Assist failed on device %x: %#x\n",
				 CARD_DEVID(card), rc);
		QETH_CARD_TEXT_(card, 2, "1err%04x", rc);
		/* fall back once more: */
	}

	/* some devices don't support a custom MAC address: */
	if (IS_OSM(card) || IS_OSX(card))
		return (rc) ? rc : -EADDRNOTAVAIL;
	eth_hw_addr_random(card->dev);

out:
	QETH_CARD_HEX(card, 2, card->dev->dev_addr, card->dev->addr_len);
	return 0;
}