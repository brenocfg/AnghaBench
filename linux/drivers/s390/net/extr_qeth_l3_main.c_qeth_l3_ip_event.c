#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* mask; void* addr; } ;
struct TYPE_5__ {TYPE_1__ a4; } ;
struct qeth_ipaddr {TYPE_2__ u; } ;
struct qeth_card {int dummy; } ;
struct notifier_block {int dummy; } ;
struct net_device {int dummy; } ;
struct in_ifaddr {int /*<<< orphan*/  ifa_mask; int /*<<< orphan*/  ifa_address; TYPE_3__* ifa_dev; } ;
struct TYPE_6__ {struct net_device* dev; } ;

/* Variables and functions */
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_IP_TYPE_NORMAL ; 
 int /*<<< orphan*/  QETH_PROT_IPV4 ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dev_net (struct net_device*) ; 
 int /*<<< orphan*/  init_net ; 
 struct qeth_card* qeth_l3_get_card_from_dev (struct net_device*) ; 
 int qeth_l3_handle_ip_event (struct qeth_card*,struct qeth_ipaddr*,unsigned long) ; 
 int /*<<< orphan*/  qeth_l3_init_ipaddr (struct qeth_ipaddr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qeth_l3_ip_event(struct notifier_block *this,
			    unsigned long event, void *ptr)
{

	struct in_ifaddr *ifa = (struct in_ifaddr *)ptr;
	struct net_device *dev = ifa->ifa_dev->dev;
	struct qeth_ipaddr addr;
	struct qeth_card *card;

	if (dev_net(dev) != &init_net)
		return NOTIFY_DONE;

	card = qeth_l3_get_card_from_dev(dev);
	if (!card)
		return NOTIFY_DONE;
	QETH_CARD_TEXT(card, 3, "ipevent");

	qeth_l3_init_ipaddr(&addr, QETH_IP_TYPE_NORMAL, QETH_PROT_IPV4);
	addr.u.a4.addr = be32_to_cpu(ifa->ifa_address);
	addr.u.a4.mask = be32_to_cpu(ifa->ifa_mask);

	return qeth_l3_handle_ip_event(card, &addr, event);
}