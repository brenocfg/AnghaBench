#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {char addr; } ;
struct TYPE_5__ {char addr; } ;
struct TYPE_7__ {TYPE_2__ a6; TYPE_1__ a4; } ;
struct qeth_ipaddr {scalar_t__ type; scalar_t__ proto; int ref_counter; int ipato; int in_progress; int /*<<< orphan*/  hnode; int /*<<< orphan*/  disp_flag; TYPE_3__ u; } ;
struct qeth_card {int /*<<< orphan*/  ip_lock; int /*<<< orphan*/  ip_htable; TYPE_4__* gdev; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EADDRINUSE ; 
 int ENETDOWN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  QETH_CARD_HEX (struct qeth_card*,int,char*,int) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_DISP_ADDR_ADD ; 
 int /*<<< orphan*/  QETH_DISP_ADDR_DO_NOTHING ; 
 scalar_t__ QETH_IP_TYPE_NORMAL ; 
 scalar_t__ QETH_IP_TYPE_RXIP ; 
 scalar_t__ QETH_IP_TYPE_VIPA ; 
 scalar_t__ QETH_PROT_IPV4 ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  hash_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct qeth_ipaddr*) ; 
 int /*<<< orphan*/  memcpy (struct qeth_ipaddr*,struct qeth_ipaddr*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qeth_card_hw_is_reachable (struct qeth_card*) ; 
 scalar_t__ qeth_l3_addr_match_all (struct qeth_ipaddr*,struct qeth_ipaddr*) ; 
 int /*<<< orphan*/  qeth_l3_deregister_addr_entry (struct qeth_card*,struct qeth_ipaddr*) ; 
 struct qeth_ipaddr* qeth_l3_find_addr_by_ip (struct qeth_card*,struct qeth_ipaddr*) ; 
 struct qeth_ipaddr* qeth_l3_get_addr_buffer (scalar_t__) ; 
 int /*<<< orphan*/  qeth_l3_ipaddr_hash (struct qeth_ipaddr*) ; 
 int /*<<< orphan*/  qeth_l3_ipaddr_to_string (scalar_t__,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ qeth_l3_is_addr_covered_by_ipato (struct qeth_card*,struct qeth_ipaddr*) ; 
 int qeth_l3_register_addr_entry (struct qeth_card*,struct qeth_ipaddr*) ; 

__attribute__((used)) static int qeth_l3_add_ip(struct qeth_card *card, struct qeth_ipaddr *tmp_addr)
{
	int rc = 0;
	struct qeth_ipaddr *addr;
	char buf[40];

	if (tmp_addr->type == QETH_IP_TYPE_RXIP)
		QETH_CARD_TEXT(card, 2, "addrxip");
	else if (tmp_addr->type == QETH_IP_TYPE_VIPA)
		QETH_CARD_TEXT(card, 2, "addvipa");
	else
		QETH_CARD_TEXT(card, 2, "addip");

	if (tmp_addr->proto == QETH_PROT_IPV4)
		QETH_CARD_HEX(card, 4, &tmp_addr->u.a4.addr, 4);
	else {
		QETH_CARD_HEX(card, 4, &tmp_addr->u.a6.addr, 8);
		QETH_CARD_HEX(card, 4, ((char *)&tmp_addr->u.a6.addr) + 8, 8);
	}

	addr = qeth_l3_find_addr_by_ip(card, tmp_addr);
	if (addr) {
		if (tmp_addr->type != QETH_IP_TYPE_NORMAL)
			return -EADDRINUSE;
		if (qeth_l3_addr_match_all(addr, tmp_addr)) {
			addr->ref_counter++;
			return 0;
		}
		qeth_l3_ipaddr_to_string(tmp_addr->proto, (u8 *)&tmp_addr->u,
					 buf);
		dev_warn(&card->gdev->dev,
			 "Registering IP address %s failed\n", buf);
		return -EADDRINUSE;
	} else {
		addr = qeth_l3_get_addr_buffer(tmp_addr->proto);
		if (!addr)
			return -ENOMEM;

		memcpy(addr, tmp_addr, sizeof(struct qeth_ipaddr));
		addr->ref_counter = 1;

		if (qeth_l3_is_addr_covered_by_ipato(card, addr)) {
			QETH_CARD_TEXT(card, 2, "tkovaddr");
			addr->ipato = 1;
		}
		hash_add(card->ip_htable, &addr->hnode,
				qeth_l3_ipaddr_hash(addr));

		if (!qeth_card_hw_is_reachable(card)) {
			addr->disp_flag = QETH_DISP_ADDR_ADD;
			return 0;
		}

		/* qeth_l3_register_addr_entry can go to sleep
		 * if we add a IPV4 addr. It is caused by the reason
		 * that SETIP ipa cmd starts ARP staff for IPV4 addr.
		 * Thus we should unlock spinlock, and make a protection
		 * using in_progress variable to indicate that there is
		 * an hardware operation with this IPV4 address
		 */
		if (addr->proto == QETH_PROT_IPV4) {
			addr->in_progress = 1;
			mutex_unlock(&card->ip_lock);
			rc = qeth_l3_register_addr_entry(card, addr);
			mutex_lock(&card->ip_lock);
			addr->in_progress = 0;
		} else
			rc = qeth_l3_register_addr_entry(card, addr);

		if (!rc || rc == -EADDRINUSE || rc == -ENETDOWN) {
			addr->disp_flag = QETH_DISP_ADDR_DO_NOTHING;
			if (addr->ref_counter < 1) {
				qeth_l3_deregister_addr_entry(card, addr);
				hash_del(&addr->hnode);
				kfree(addr);
			}
		} else {
			hash_del(&addr->hnode);
			kfree(addr);
		}
	}
	return rc;
}