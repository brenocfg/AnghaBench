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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp_mr_tcam_erif_list {int /*<<< orphan*/  kvdl_index; } ;
struct mlxsw_sp {int /*<<< orphan*/  afa; } ;
struct mlxsw_afa_block {int dummy; } ;
typedef  enum mlxsw_sp_mr_route_action { ____Placeholder_mlxsw_sp_mr_route_action } mlxsw_sp_mr_route_action ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct mlxsw_afa_block* ERR_PTR (int) ; 
#define  MLXSW_SP_MR_ROUTE_ACTION_FORWARD 130 
#define  MLXSW_SP_MR_ROUTE_ACTION_TRAP 129 
#define  MLXSW_SP_MR_ROUTE_ACTION_TRAP_AND_FORWARD 128 
 int /*<<< orphan*/  MLXSW_TRAP_ID_ACL1 ; 
 int /*<<< orphan*/  MLXSW_TRAP_ID_ACL2 ; 
 int mlxsw_afa_block_append_allocated_counter (struct mlxsw_afa_block*,int /*<<< orphan*/ ) ; 
 int mlxsw_afa_block_append_mcrouter (struct mlxsw_afa_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int mlxsw_afa_block_append_trap (struct mlxsw_afa_block*,int /*<<< orphan*/ ) ; 
 int mlxsw_afa_block_append_trap_and_forward (struct mlxsw_afa_block*,int /*<<< orphan*/ ) ; 
 int mlxsw_afa_block_commit (struct mlxsw_afa_block*) ; 
 struct mlxsw_afa_block* mlxsw_afa_block_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_afa_block_destroy (struct mlxsw_afa_block*) ; 
 int mlxsw_sp_mr_erif_list_commit (struct mlxsw_sp*,struct mlxsw_sp_mr_tcam_erif_list*) ; 

__attribute__((used)) static struct mlxsw_afa_block *
mlxsw_sp_mr_tcam_afa_block_create(struct mlxsw_sp *mlxsw_sp,
				  enum mlxsw_sp_mr_route_action route_action,
				  u16 irif_index, u32 counter_index,
				  u16 min_mtu,
				  struct mlxsw_sp_mr_tcam_erif_list *erif_list)
{
	struct mlxsw_afa_block *afa_block;
	int err;

	afa_block = mlxsw_afa_block_create(mlxsw_sp->afa);
	if (!afa_block)
		return ERR_PTR(-ENOMEM);

	err = mlxsw_afa_block_append_allocated_counter(afa_block,
						       counter_index);
	if (err)
		goto err;

	switch (route_action) {
	case MLXSW_SP_MR_ROUTE_ACTION_TRAP:
		err = mlxsw_afa_block_append_trap(afa_block,
						  MLXSW_TRAP_ID_ACL1);
		if (err)
			goto err;
		break;
	case MLXSW_SP_MR_ROUTE_ACTION_TRAP_AND_FORWARD:
	case MLXSW_SP_MR_ROUTE_ACTION_FORWARD:
		/* If we are about to append a multicast router action, commit
		 * the erif_list.
		 */
		err = mlxsw_sp_mr_erif_list_commit(mlxsw_sp, erif_list);
		if (err)
			goto err;

		err = mlxsw_afa_block_append_mcrouter(afa_block, irif_index,
						      min_mtu, false,
						      erif_list->kvdl_index);
		if (err)
			goto err;

		if (route_action == MLXSW_SP_MR_ROUTE_ACTION_TRAP_AND_FORWARD) {
			err = mlxsw_afa_block_append_trap_and_forward(afa_block,
								      MLXSW_TRAP_ID_ACL2);
			if (err)
				goto err;
		}
		break;
	default:
		err = -EINVAL;
		goto err;
	}

	err = mlxsw_afa_block_commit(afa_block);
	if (err)
		goto err;
	return afa_block;
err:
	mlxsw_afa_block_destroy(afa_block);
	return ERR_PTR(err);
}