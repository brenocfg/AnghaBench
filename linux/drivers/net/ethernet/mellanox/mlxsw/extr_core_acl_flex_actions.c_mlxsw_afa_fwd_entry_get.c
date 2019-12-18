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
typedef  int /*<<< orphan*/  u8 ;
struct mlxsw_afa_fwd_entry_ht_key {int /*<<< orphan*/  local_port; int /*<<< orphan*/  member_0; } ;
struct mlxsw_afa_fwd_entry {int /*<<< orphan*/  ref_count; } ;
struct mlxsw_afa {int /*<<< orphan*/  fwd_entry_ht; } ;

/* Variables and functions */
 struct mlxsw_afa_fwd_entry* mlxsw_afa_fwd_entry_create (struct mlxsw_afa*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_afa_fwd_entry_ht_params ; 
 struct mlxsw_afa_fwd_entry* rhashtable_lookup_fast (int /*<<< orphan*/ *,struct mlxsw_afa_fwd_entry_ht_key*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlxsw_afa_fwd_entry *
mlxsw_afa_fwd_entry_get(struct mlxsw_afa *mlxsw_afa, u8 local_port)
{
	struct mlxsw_afa_fwd_entry_ht_key ht_key = {0};
	struct mlxsw_afa_fwd_entry *fwd_entry;

	ht_key.local_port = local_port;
	fwd_entry = rhashtable_lookup_fast(&mlxsw_afa->fwd_entry_ht, &ht_key,
					   mlxsw_afa_fwd_entry_ht_params);
	if (fwd_entry) {
		fwd_entry->ref_count++;
		return fwd_entry;
	}
	return mlxsw_afa_fwd_entry_create(mlxsw_afa, local_port);
}