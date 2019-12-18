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
struct mlx5e_l2_hash_node {int /*<<< orphan*/  hlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mlx5e_l2_hash_node*) ; 

__attribute__((used)) static void mlx5e_del_l2_from_hash(struct mlx5e_l2_hash_node *hn)
{
	hlist_del(&hn->hlist);
	kfree(hn);
}