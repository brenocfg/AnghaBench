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
struct TYPE_4__ {int /*<<< orphan*/  mac_bits; } ;
struct qeth_card {TYPE_2__ info; TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_OSN (struct qeth_card*) ; 
 int /*<<< orphan*/  QETH_LAYER2_MAC_REGISTERED ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_l2_request_initial_mac (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_l2_send_setmac (struct qeth_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qeth_l2_register_dev_addr(struct qeth_card *card)
{
	if (!is_valid_ether_addr(card->dev->dev_addr))
		qeth_l2_request_initial_mac(card);

	if (!IS_OSN(card) && !qeth_l2_send_setmac(card, card->dev->dev_addr))
		card->info.mac_bits |= QETH_LAYER2_MAC_REGISTERED;
}