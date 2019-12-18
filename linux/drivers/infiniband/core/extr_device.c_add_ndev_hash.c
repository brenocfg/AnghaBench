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
struct ib_port_data {scalar_t__ netdev; int /*<<< orphan*/  ndev_hash_link; } ;

/* Variables and functions */
 int /*<<< orphan*/  hash_add_rcu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,uintptr_t) ; 
 int /*<<< orphan*/  hash_del_rcu (int /*<<< orphan*/ *) ; 
 scalar_t__ hash_hashed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  ndev_hash ; 
 int /*<<< orphan*/  ndev_hash_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static void add_ndev_hash(struct ib_port_data *pdata)
{
	unsigned long flags;

	might_sleep();

	spin_lock_irqsave(&ndev_hash_lock, flags);
	if (hash_hashed(&pdata->ndev_hash_link)) {
		hash_del_rcu(&pdata->ndev_hash_link);
		spin_unlock_irqrestore(&ndev_hash_lock, flags);
		/*
		 * We cannot do hash_add_rcu after a hash_del_rcu until the
		 * grace period
		 */
		synchronize_rcu();
		spin_lock_irqsave(&ndev_hash_lock, flags);
	}
	if (pdata->netdev)
		hash_add_rcu(ndev_hash, &pdata->ndev_hash_link,
			     (uintptr_t)pdata->netdev);
	spin_unlock_irqrestore(&ndev_hash_lock, flags);
}