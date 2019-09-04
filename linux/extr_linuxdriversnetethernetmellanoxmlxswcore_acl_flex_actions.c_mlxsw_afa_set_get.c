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
struct mlxsw_afa_set {int /*<<< orphan*/  ref_count; int /*<<< orphan*/  ht_key; } ;
struct mlxsw_afa {int /*<<< orphan*/  set_ht; } ;

/* Variables and functions */
 struct mlxsw_afa_set* ERR_PTR (int) ; 
 int /*<<< orphan*/  mlxsw_afa_set_ht_params ; 
 int /*<<< orphan*/  mlxsw_afa_set_put (struct mlxsw_afa*,struct mlxsw_afa_set*) ; 
 int mlxsw_afa_set_share (struct mlxsw_afa*,struct mlxsw_afa_set*) ; 
 struct mlxsw_afa_set* rhashtable_lookup_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlxsw_afa_set *mlxsw_afa_set_get(struct mlxsw_afa *mlxsw_afa,
					       struct mlxsw_afa_set *orig_set)
{
	struct mlxsw_afa_set *set;
	int err;

	/* There is a hashtable of sets maintained. If a set with the exact
	 * same encoding exists, we reuse it. Otherwise, the current set
	 * is shared by making it available to others using the hash table.
	 */
	set = rhashtable_lookup_fast(&mlxsw_afa->set_ht, &orig_set->ht_key,
				     mlxsw_afa_set_ht_params);
	if (set) {
		set->ref_count++;
		mlxsw_afa_set_put(mlxsw_afa, orig_set);
	} else {
		set = orig_set;
		err = mlxsw_afa_set_share(mlxsw_afa, set);
		if (err)
			return ERR_PTR(err);
	}
	return set;
}