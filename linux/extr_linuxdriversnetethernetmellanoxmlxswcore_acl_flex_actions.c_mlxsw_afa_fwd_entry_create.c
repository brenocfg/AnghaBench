#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/  local_port; } ;
struct mlxsw_afa_fwd_entry {int ref_count; int /*<<< orphan*/  ht_node; int /*<<< orphan*/  kvdl_index; TYPE_2__ ht_key; } ;
struct mlxsw_afa {int /*<<< orphan*/  fwd_entry_ht; int /*<<< orphan*/  ops_priv; TYPE_1__* ops; } ;
struct TYPE_3__ {int (* kvdl_fwd_entry_add ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 struct mlxsw_afa_fwd_entry* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct mlxsw_afa_fwd_entry*) ; 
 struct mlxsw_afa_fwd_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_afa_fwd_entry_ht_params ; 
 int rhashtable_insert_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlxsw_afa_fwd_entry *
mlxsw_afa_fwd_entry_create(struct mlxsw_afa *mlxsw_afa, u8 local_port)
{
	struct mlxsw_afa_fwd_entry *fwd_entry;
	int err;

	fwd_entry = kzalloc(sizeof(*fwd_entry), GFP_KERNEL);
	if (!fwd_entry)
		return ERR_PTR(-ENOMEM);
	fwd_entry->ht_key.local_port = local_port;
	fwd_entry->ref_count = 1;

	err = rhashtable_insert_fast(&mlxsw_afa->fwd_entry_ht,
				     &fwd_entry->ht_node,
				     mlxsw_afa_fwd_entry_ht_params);
	if (err)
		goto err_rhashtable_insert;

	err = mlxsw_afa->ops->kvdl_fwd_entry_add(mlxsw_afa->ops_priv,
						 &fwd_entry->kvdl_index,
						 local_port);
	if (err)
		goto err_kvdl_fwd_entry_add;
	return fwd_entry;

err_kvdl_fwd_entry_add:
	rhashtable_remove_fast(&mlxsw_afa->fwd_entry_ht, &fwd_entry->ht_node,
			       mlxsw_afa_fwd_entry_ht_params);
err_rhashtable_insert:
	kfree(fwd_entry);
	return ERR_PTR(err);
}