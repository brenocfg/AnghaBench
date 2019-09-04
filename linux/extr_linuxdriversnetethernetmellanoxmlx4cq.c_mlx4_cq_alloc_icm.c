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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_CMD_ALLOC_RES ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_A ; 
 int /*<<< orphan*/  MLX4_CMD_WRAPPED ; 
 int RES_CQ ; 
 int /*<<< orphan*/  RES_OP_RESERVE_AND_MAP ; 
 int __mlx4_cq_alloc_icm (struct mlx4_dev*,int*) ; 
 int get_param_l (int /*<<< orphan*/ *) ; 
 int mlx4_cmd_imm (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx4_is_mfunc (struct mlx4_dev*) ; 

__attribute__((used)) static int mlx4_cq_alloc_icm(struct mlx4_dev *dev, int *cqn, u8 usage)
{
	u32 in_modifier = RES_CQ | (((u32)usage & 3) << 30);
	u64 out_param;
	int err;

	if (mlx4_is_mfunc(dev)) {
		err = mlx4_cmd_imm(dev, 0, &out_param, in_modifier,
				   RES_OP_RESERVE_AND_MAP, MLX4_CMD_ALLOC_RES,
				   MLX4_CMD_TIME_CLASS_A, MLX4_CMD_WRAPPED);
		if (err)
			return err;
		else {
			*cqn = get_param_l(&out_param);
			return 0;
		}
	}
	return __mlx4_cq_alloc_icm(dev, cqn);
}