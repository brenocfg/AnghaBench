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
struct mlx5e_ipsec_sa_entry {int handle; int /*<<< orphan*/  hlist; struct mlx5e_ipsec* ipsec; } ;
struct mlx5e_ipsec {int /*<<< orphan*/  sadb_rx_lock; int /*<<< orphan*/  sadb_rx; int /*<<< orphan*/  halloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  hash_add_rcu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int mlx5e_ipsec_sadb_rx_add(struct mlx5e_ipsec_sa_entry *sa_entry)
{
	struct mlx5e_ipsec *ipsec = sa_entry->ipsec;
	unsigned long flags;
	int ret;

	ret = ida_simple_get(&ipsec->halloc, 1, 0, GFP_KERNEL);
	if (ret < 0)
		return ret;

	spin_lock_irqsave(&ipsec->sadb_rx_lock, flags);
	sa_entry->handle = ret;
	hash_add_rcu(ipsec->sadb_rx, &sa_entry->hlist, sa_entry->handle);
	spin_unlock_irqrestore(&ipsec->sadb_rx_lock, flags);

	return 0;
}