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
struct hwsim_pib {int dummy; } ;
struct hwsim_phy {int /*<<< orphan*/  hw; int /*<<< orphan*/  pib; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  hwsim_edge_unsubscribe_me (struct hwsim_phy*) ; 
 int /*<<< orphan*/  ieee802154_free_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee802154_unregister_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_rcu (struct hwsim_pib*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu ; 
 struct hwsim_pib* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void hwsim_del(struct hwsim_phy *phy)
{
	struct hwsim_pib *pib;

	hwsim_edge_unsubscribe_me(phy);

	list_del(&phy->list);

	rcu_read_lock();
	pib = rcu_dereference(phy->pib);
	rcu_read_unlock();

	kfree_rcu(pib, rcu);

	ieee802154_unregister_hw(phy->hw);
	ieee802154_free_hw(phy->hw);
}