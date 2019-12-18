#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_8__ {int hdr_modify_icm_addr; } ;
struct TYPE_9__ {TYPE_2__ caps; } ;
struct mlx5dr_domain {TYPE_3__ info; int /*<<< orphan*/  action_icm_pool; int /*<<< orphan*/  mdev; } ;
struct TYPE_10__ {int index; TYPE_5__* chunk; } ;
struct TYPE_7__ {size_t reformat_size; int /*<<< orphan*/  reformat_id; } ;
struct mlx5dr_action {int action_type; TYPE_4__ rewrite; TYPE_1__ reformat; } ;
typedef  enum mlx5_reformat_ctx_type { ____Placeholder_mlx5_reformat_ctx_type } mlx5_reformat_ctx_type ;
struct TYPE_11__ {int icm_addr; } ;

/* Variables and functions */
 int ACTION_CACHE_LINE_SIZE ; 
#define  DR_ACTION_TYP_L2_TO_TNL_L2 131 
#define  DR_ACTION_TYP_L2_TO_TNL_L3 130 
#define  DR_ACTION_TYP_TNL_L2_TO_L2 129 
#define  DR_ACTION_TYP_TNL_L3_TO_L2 128 
 int /*<<< orphan*/  DR_CHUNK_SIZE_8 ; 
 int EINVAL ; 
 int ENOMEM ; 
 size_t HDR_LEN_L2_ONLY ; 
 size_t HDR_LEN_L2_VLAN ; 
 int MLX5_REFORMAT_TYPE_L2_TO_L2_TUNNEL ; 
 int MLX5_REFORMAT_TYPE_L2_TO_L3_TUNNEL ; 
 int dr_actions_l2_rewrite (struct mlx5dr_domain*,struct mlx5dr_action*,void*,size_t) ; 
 int mlx5dr_cmd_create_reformat_ctx (int /*<<< orphan*/ ,int,size_t,void*,int /*<<< orphan*/ *) ; 
 TYPE_5__* mlx5dr_icm_alloc_chunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5dr_icm_free_chunk (TYPE_5__*) ; 
 int /*<<< orphan*/  mlx5dr_info (struct mlx5dr_domain*,char*,int const) ; 

__attribute__((used)) static int
dr_action_create_reformat_action(struct mlx5dr_domain *dmn,
				 size_t data_sz, void *data,
				 struct mlx5dr_action *action)
{
	u32 reformat_id;
	int ret;

	switch (action->action_type) {
	case DR_ACTION_TYP_L2_TO_TNL_L2:
	case DR_ACTION_TYP_L2_TO_TNL_L3:
	{
		enum mlx5_reformat_ctx_type rt;

		if (action->action_type == DR_ACTION_TYP_L2_TO_TNL_L2)
			rt = MLX5_REFORMAT_TYPE_L2_TO_L2_TUNNEL;
		else
			rt = MLX5_REFORMAT_TYPE_L2_TO_L3_TUNNEL;

		ret = mlx5dr_cmd_create_reformat_ctx(dmn->mdev, rt, data_sz, data,
						     &reformat_id);
		if (ret)
			return ret;

		action->reformat.reformat_id = reformat_id;
		action->reformat.reformat_size = data_sz;
		return 0;
	}
	case DR_ACTION_TYP_TNL_L2_TO_L2:
	{
		return 0;
	}
	case DR_ACTION_TYP_TNL_L3_TO_L2:
	{
		/* Only Ethernet frame is supported, with VLAN (18) or without (14) */
		if (data_sz != HDR_LEN_L2_ONLY && data_sz != HDR_LEN_L2_VLAN)
			return -EINVAL;

		action->rewrite.chunk = mlx5dr_icm_alloc_chunk(dmn->action_icm_pool,
							       DR_CHUNK_SIZE_8);
		if (!action->rewrite.chunk)
			return -ENOMEM;

		action->rewrite.index = (action->rewrite.chunk->icm_addr -
					 dmn->info.caps.hdr_modify_icm_addr) /
					 ACTION_CACHE_LINE_SIZE;

		ret = dr_actions_l2_rewrite(dmn, action, data, data_sz);
		if (ret) {
			mlx5dr_icm_free_chunk(action->rewrite.chunk);
			return ret;
		}
		return 0;
	}
	default:
		mlx5dr_info(dmn, "Reformat type is not supported %d\n", action->action_type);
		return -EINVAL;
	}
}