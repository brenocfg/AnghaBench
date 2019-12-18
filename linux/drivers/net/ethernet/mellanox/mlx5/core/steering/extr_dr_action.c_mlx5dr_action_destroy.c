#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_5__* dmn; struct mlx5dr_action* data; int /*<<< orphan*/  chunk; } ;
struct TYPE_10__ {TYPE_3__* dmn; int /*<<< orphan*/  reformat_id; } ;
struct TYPE_8__ {TYPE_1__* tbl; int /*<<< orphan*/  is_fw_tbl; } ;
struct mlx5dr_action {int action_type; TYPE_6__ rewrite; TYPE_4__ reformat; TYPE_2__ dest_tbl; int /*<<< orphan*/  refcount; } ;
struct TYPE_11__ {int /*<<< orphan*/  refcount; } ;
struct TYPE_9__ {int /*<<< orphan*/  refcount; int /*<<< orphan*/  mdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
#define  DR_ACTION_TYP_FT 133 
#define  DR_ACTION_TYP_L2_TO_TNL_L2 132 
#define  DR_ACTION_TYP_L2_TO_TNL_L3 131 
#define  DR_ACTION_TYP_MODIFY_HDR 130 
#define  DR_ACTION_TYP_TNL_L2_TO_L2 129 
#define  DR_ACTION_TYP_TNL_L3_TO_L2 128 
 int EBUSY ; 
 int /*<<< orphan*/  kfree (struct mlx5dr_action*) ; 
 int /*<<< orphan*/  mlx5dr_cmd_destroy_reformat_ctx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5dr_icm_free_chunk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_dec (int /*<<< orphan*/ *) ; 
 int refcount_read (int /*<<< orphan*/ *) ; 

int mlx5dr_action_destroy(struct mlx5dr_action *action)
{
	if (refcount_read(&action->refcount) > 1)
		return -EBUSY;

	switch (action->action_type) {
	case DR_ACTION_TYP_FT:
		if (!action->dest_tbl.is_fw_tbl)
			refcount_dec(&action->dest_tbl.tbl->refcount);
		break;
	case DR_ACTION_TYP_TNL_L2_TO_L2:
		refcount_dec(&action->reformat.dmn->refcount);
		break;
	case DR_ACTION_TYP_TNL_L3_TO_L2:
		mlx5dr_icm_free_chunk(action->rewrite.chunk);
		refcount_dec(&action->reformat.dmn->refcount);
		break;
	case DR_ACTION_TYP_L2_TO_TNL_L2:
	case DR_ACTION_TYP_L2_TO_TNL_L3:
		mlx5dr_cmd_destroy_reformat_ctx((action->reformat.dmn)->mdev,
						action->reformat.reformat_id);
		refcount_dec(&action->reformat.dmn->refcount);
		break;
	case DR_ACTION_TYP_MODIFY_HDR:
		mlx5dr_icm_free_chunk(action->rewrite.chunk);
		kfree(action->rewrite.data);
		refcount_dec(&action->rewrite.dmn->refcount);
		break;
	default:
		break;
	}

	kfree(action);
	return 0;
}