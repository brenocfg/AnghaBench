#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ipvl_dev {int /*<<< orphan*/  addrs_lock; } ;
struct ipvl_addr {int /*<<< orphan*/  anode; } ;

/* Variables and functions */
 struct ipvl_addr* ipvlan_find_addr (struct ipvl_dev*,void*,int) ; 
 int /*<<< orphan*/  ipvlan_ht_addr_del (struct ipvl_addr*) ; 
 int /*<<< orphan*/  kfree_rcu (struct ipvl_addr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipvlan_del_addr(struct ipvl_dev *ipvlan, void *iaddr, bool is_v6)
{
	struct ipvl_addr *addr;

	spin_lock_bh(&ipvlan->addrs_lock);
	addr = ipvlan_find_addr(ipvlan, iaddr, is_v6);
	if (!addr) {
		spin_unlock_bh(&ipvlan->addrs_lock);
		return;
	}

	ipvlan_ht_addr_del(addr);
	list_del_rcu(&addr->anode);
	spin_unlock_bh(&ipvlan->addrs_lock);
	kfree_rcu(addr, rcu);
}