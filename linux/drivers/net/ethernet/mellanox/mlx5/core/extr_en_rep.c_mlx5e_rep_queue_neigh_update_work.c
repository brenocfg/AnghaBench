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
struct neighbour {int dummy; } ;
struct mlx5e_priv {int /*<<< orphan*/  wq; } ;
struct mlx5e_neigh_hash_entry {int /*<<< orphan*/  neigh_update_work; struct neighbour* n; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_rep_neigh_entry_release (struct mlx5e_neigh_hash_entry*) ; 
 int /*<<< orphan*/  neigh_hold (struct neighbour*) ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlx5e_rep_queue_neigh_update_work(struct mlx5e_priv *priv,
				  struct mlx5e_neigh_hash_entry *nhe,
				  struct neighbour *n)
{
	/* Take a reference to ensure the neighbour and mlx5 encap
	 * entry won't be destructed until we drop the reference in
	 * delayed work.
	 */
	neigh_hold(n);

	/* This assignment is valid as long as the the neigh reference
	 * is taken
	 */
	nhe->n = n;

	if (!queue_work(priv->wq, &nhe->neigh_update_work)) {
		mlx5e_rep_neigh_entry_release(nhe);
		neigh_release(n);
	}
}