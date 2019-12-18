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
typedef  int /*<<< orphan*/  u8 ;
struct sockaddr {int /*<<< orphan*/ * sa_data; } ;
struct TYPE_2__ {int mac_bits; } ;
struct qeth_card {TYPE_1__ info; } ;
struct net_device {int /*<<< orphan*/ * dev_addr; struct qeth_card* ml_priv; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int EOPNOTSUPP ; 
 int ETH_ALEN ; 
 scalar_t__ IS_OSM (struct qeth_card*) ; 
 scalar_t__ IS_OSX (struct qeth_card*) ; 
 int /*<<< orphan*/  QETH_CARD_HEX (struct qeth_card*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int QETH_LAYER2_MAC_REGISTERED ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ether_addr_equal_64bits (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qeth_l2_remove_mac (struct qeth_card*,int /*<<< orphan*/ *) ; 
 int qeth_l2_send_setmac (struct qeth_card*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qeth_l2_set_mac_address(struct net_device *dev, void *p)
{
	struct sockaddr *addr = p;
	struct qeth_card *card = dev->ml_priv;
	u8 old_addr[ETH_ALEN];
	int rc = 0;

	QETH_CARD_TEXT(card, 3, "setmac");

	if (IS_OSM(card) || IS_OSX(card)) {
		QETH_CARD_TEXT(card, 3, "setmcTYP");
		return -EOPNOTSUPP;
	}
	QETH_CARD_HEX(card, 3, addr->sa_data, ETH_ALEN);
	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	/* don't register the same address twice */
	if (ether_addr_equal_64bits(dev->dev_addr, addr->sa_data) &&
	    (card->info.mac_bits & QETH_LAYER2_MAC_REGISTERED))
		return 0;

	/* add the new address, switch over, drop the old */
	rc = qeth_l2_send_setmac(card, addr->sa_data);
	if (rc)
		return rc;
	ether_addr_copy(old_addr, dev->dev_addr);
	ether_addr_copy(dev->dev_addr, addr->sa_data);

	if (card->info.mac_bits & QETH_LAYER2_MAC_REGISTERED)
		qeth_l2_remove_mac(card, old_addr);
	card->info.mac_bits |= QETH_LAYER2_MAC_REGISTERED;
	return 0;
}