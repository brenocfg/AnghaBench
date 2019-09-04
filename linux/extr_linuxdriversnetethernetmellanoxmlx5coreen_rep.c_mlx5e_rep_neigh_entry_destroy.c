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
struct mlx5e_priv {int dummy; } ;
struct mlx5e_neigh_hash_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_rep_neigh_entry_release (struct mlx5e_neigh_hash_entry*) ; 
 int /*<<< orphan*/  mlx5e_rep_neigh_entry_remove (struct mlx5e_priv*,struct mlx5e_neigh_hash_entry*) ; 

__attribute__((used)) static void mlx5e_rep_neigh_entry_destroy(struct mlx5e_priv *priv,
					  struct mlx5e_neigh_hash_entry *nhe)
{
	/* The neigh hash entry must be removed from the hash table regardless
	 * of the reference count value, so it won't be found by the next
	 * neigh notification call. The neigh hash entry reference count is
	 * incremented only during creation and neigh notification calls and
	 * protects from freeing the nhe struct.
	 */
	mlx5e_rep_neigh_entry_remove(priv, nhe);
	mlx5e_rep_neigh_entry_release(nhe);
}