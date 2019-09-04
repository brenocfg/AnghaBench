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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ alloc_res_qp_mask; } ;
struct mlx4_dev {TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_CMD_ALLOC_RES ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_A ; 
 int /*<<< orphan*/  MLX4_CMD_WRAPPED ; 
 int /*<<< orphan*/  RES_OP_RESERVE ; 
 int RES_QP ; 
 int __mlx4_qp_reserve_range (struct mlx4_dev*,int,int,int*,scalar_t__) ; 
 int get_param_l (int /*<<< orphan*/ *) ; 
 int mlx4_cmd_imm (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx4_is_mfunc (struct mlx4_dev*) ; 
 int /*<<< orphan*/  set_param_h (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_param_l (int /*<<< orphan*/ *,int) ; 

int mlx4_qp_reserve_range(struct mlx4_dev *dev, int cnt, int align,
			  int *base, u8 flags, u8 usage)
{
	u32 in_modifier = RES_QP | (((u32)usage & 3) << 30);
	u64 in_param = 0;
	u64 out_param;
	int err;

	/* Turn off all unsupported QP allocation flags */
	flags &= dev->caps.alloc_res_qp_mask;

	if (mlx4_is_mfunc(dev)) {
		set_param_l(&in_param, (((u32)flags) << 24) | (u32)cnt);
		set_param_h(&in_param, align);
		err = mlx4_cmd_imm(dev, in_param, &out_param,
				   in_modifier, RES_OP_RESERVE,
				   MLX4_CMD_ALLOC_RES,
				   MLX4_CMD_TIME_CLASS_A, MLX4_CMD_WRAPPED);
		if (err)
			return err;

		*base = get_param_l(&out_param);
		return 0;
	}
	return __mlx4_qp_reserve_range(dev, cnt, align, base, flags);
}