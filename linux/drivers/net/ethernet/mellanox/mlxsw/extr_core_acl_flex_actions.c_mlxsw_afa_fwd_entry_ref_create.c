#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  destructor; } ;
struct mlxsw_afa_fwd_entry_ref {TYPE_1__ resource; struct mlxsw_afa_fwd_entry* fwd_entry; } ;
struct mlxsw_afa_fwd_entry {int dummy; } ;
struct mlxsw_afa_block {int /*<<< orphan*/  afa; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct mlxsw_afa_fwd_entry_ref* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct mlxsw_afa_fwd_entry*) ; 
 int PTR_ERR (struct mlxsw_afa_fwd_entry*) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_afa_fwd_entry_ref*) ; 
 struct mlxsw_afa_fwd_entry_ref* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct mlxsw_afa_fwd_entry* mlxsw_afa_fwd_entry_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_afa_fwd_entry_ref_destructor ; 
 int /*<<< orphan*/  mlxsw_afa_resource_add (struct mlxsw_afa_block*,TYPE_1__*) ; 

__attribute__((used)) static struct mlxsw_afa_fwd_entry_ref *
mlxsw_afa_fwd_entry_ref_create(struct mlxsw_afa_block *block, u8 local_port)
{
	struct mlxsw_afa_fwd_entry_ref *fwd_entry_ref;
	struct mlxsw_afa_fwd_entry *fwd_entry;
	int err;

	fwd_entry_ref = kzalloc(sizeof(*fwd_entry_ref), GFP_KERNEL);
	if (!fwd_entry_ref)
		return ERR_PTR(-ENOMEM);
	fwd_entry = mlxsw_afa_fwd_entry_get(block->afa, local_port);
	if (IS_ERR(fwd_entry)) {
		err = PTR_ERR(fwd_entry);
		goto err_fwd_entry_get;
	}
	fwd_entry_ref->fwd_entry = fwd_entry;
	fwd_entry_ref->resource.destructor = mlxsw_afa_fwd_entry_ref_destructor;
	mlxsw_afa_resource_add(block, &fwd_entry_ref->resource);
	return fwd_entry_ref;

err_fwd_entry_get:
	kfree(fwd_entry_ref);
	return ERR_PTR(err);
}