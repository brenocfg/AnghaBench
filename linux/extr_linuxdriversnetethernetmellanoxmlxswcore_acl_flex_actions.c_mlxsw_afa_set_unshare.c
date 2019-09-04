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
struct TYPE_4__ {int /*<<< orphan*/  is_first; } ;
struct mlxsw_afa_set {int shared; int /*<<< orphan*/  ht_node; TYPE_2__ ht_key; int /*<<< orphan*/  kvdl_index; } ;
struct mlxsw_afa {int /*<<< orphan*/  set_ht; int /*<<< orphan*/  ops_priv; TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* kvdl_set_del ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_afa_set_ht_params ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_afa_set_unshare(struct mlxsw_afa *mlxsw_afa,
				  struct mlxsw_afa_set *set)
{
	mlxsw_afa->ops->kvdl_set_del(mlxsw_afa->ops_priv,
				     set->kvdl_index,
				     set->ht_key.is_first);
	rhashtable_remove_fast(&mlxsw_afa->set_ht, &set->ht_node,
			       mlxsw_afa_set_ht_params);
	set->shared = false;
}