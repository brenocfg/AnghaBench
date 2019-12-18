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
struct TYPE_2__ {int mac_bits; } ;
struct qeth_card {TYPE_1__ info; } ;
struct net_device {struct qeth_card* ml_priv; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int QETH_LAYER2_MAC_REGISTERED ; 
 int eth_validate_addr (struct net_device*) ; 

__attribute__((used)) static int qeth_l2_validate_addr(struct net_device *dev)
{
	struct qeth_card *card = dev->ml_priv;

	if (card->info.mac_bits & QETH_LAYER2_MAC_REGISTERED)
		return eth_validate_addr(dev);

	QETH_CARD_TEXT(card, 4, "nomacadr");
	return -EPERM;
}