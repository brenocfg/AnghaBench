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
struct mlx5e_neigh_hash_entry {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_rcu (struct mlx5e_neigh_hash_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_rep_neigh_entry_remove (struct mlx5e_neigh_hash_entry*) ; 
 int /*<<< orphan*/  rcu ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5e_rep_neigh_entry_release(struct mlx5e_neigh_hash_entry *nhe)
{
	if (refcount_dec_and_test(&nhe->refcnt)) {
		mlx5e_rep_neigh_entry_remove(nhe);
		kfree_rcu(nhe, rcu);
	}
}