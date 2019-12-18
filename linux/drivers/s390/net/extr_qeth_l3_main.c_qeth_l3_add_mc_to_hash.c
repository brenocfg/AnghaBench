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
struct TYPE_3__ {void* addr; } ;
struct TYPE_4__ {TYPE_1__ a4; } ;
struct qeth_ipaddr {int is_multicast; int /*<<< orphan*/  hnode; int /*<<< orphan*/  disp_flag; TYPE_2__ u; int /*<<< orphan*/  mac; } ;
struct qeth_card {int /*<<< orphan*/  ip_mc_htable; } ;
struct ip_mc_list {int /*<<< orphan*/  multiaddr; int /*<<< orphan*/  next_rcu; } ;
struct in_device {int /*<<< orphan*/  mc_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_DISP_ADDR_ADD ; 
 int /*<<< orphan*/  QETH_DISP_ADDR_DO_NOTHING ; 
 int /*<<< orphan*/  QETH_PROT_IPV4 ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_eth_mc_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qeth_ipaddr*) ; 
 struct qeth_ipaddr* qeth_l3_find_addr_by_ip (struct qeth_card*,struct qeth_ipaddr*) ; 
 struct qeth_ipaddr* qeth_l3_get_addr_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_l3_ipaddr_hash (struct qeth_ipaddr*) ; 
 struct ip_mc_list* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qeth_l3_add_mc_to_hash(struct qeth_card *card, struct in_device *in4_dev)
{
	struct ip_mc_list *im4;
	struct qeth_ipaddr *tmp, *ipm;

	QETH_CARD_TEXT(card, 4, "addmc");

	tmp = qeth_l3_get_addr_buffer(QETH_PROT_IPV4);
	if (!tmp)
		return;

	for (im4 = rcu_dereference(in4_dev->mc_list); im4 != NULL;
	     im4 = rcu_dereference(im4->next_rcu)) {
		ip_eth_mc_map(im4->multiaddr, tmp->mac);
		tmp->u.a4.addr = be32_to_cpu(im4->multiaddr);
		tmp->is_multicast = 1;

		ipm = qeth_l3_find_addr_by_ip(card, tmp);
		if (ipm) {
			/* for mcast, by-IP match means full match */
			ipm->disp_flag = QETH_DISP_ADDR_DO_NOTHING;
		} else {
			ipm = qeth_l3_get_addr_buffer(QETH_PROT_IPV4);
			if (!ipm)
				continue;
			ether_addr_copy(ipm->mac, tmp->mac);
			ipm->u.a4.addr = be32_to_cpu(im4->multiaddr);
			ipm->is_multicast = 1;
			ipm->disp_flag = QETH_DISP_ADDR_ADD;
			hash_add(card->ip_mc_htable,
					&ipm->hnode, qeth_l3_ipaddr_hash(ipm));
		}
	}

	kfree(tmp);
}