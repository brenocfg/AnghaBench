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
typedef  int /*<<< orphan*/  u64 ;
struct res_mpt {int /*<<< orphan*/  key; } ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RES_MPT ; 
 int /*<<< orphan*/  RES_MPT_MAPPED ; 
#define  RES_OP_MAP_ICM 129 
#define  RES_OP_RESERVE 128 
 int __mlx4_mpt_alloc_icm (struct mlx4_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __mlx4_mpt_release (struct mlx4_dev*,int) ; 
 int __mlx4_mpt_reserve (struct mlx4_dev*) ; 
 int add_res_range (struct mlx4_dev*,int,int,int,int /*<<< orphan*/ ,int) ; 
 int get_param_l (int /*<<< orphan*/ *) ; 
 int mlx4_grant_resource (struct mlx4_dev*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_release_resource (struct mlx4_dev*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int mpt_mask (struct mlx4_dev*) ; 
 int mr_res_start_move_to (struct mlx4_dev*,int,int,int /*<<< orphan*/ ,struct res_mpt**) ; 
 int /*<<< orphan*/  res_abort_move (struct mlx4_dev*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  res_end_move (struct mlx4_dev*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_param_l (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mpt_alloc_res(struct mlx4_dev *dev, int slave, int op, int cmd,
			 u64 in_param, u64 *out_param)
{
	int err = -EINVAL;
	int index;
	int id;
	struct res_mpt *mpt;

	switch (op) {
	case RES_OP_RESERVE:
		err = mlx4_grant_resource(dev, slave, RES_MPT, 1, 0);
		if (err)
			break;

		index = __mlx4_mpt_reserve(dev);
		if (index == -1) {
			mlx4_release_resource(dev, slave, RES_MPT, 1, 0);
			break;
		}
		id = index & mpt_mask(dev);

		err = add_res_range(dev, slave, id, 1, RES_MPT, index);
		if (err) {
			mlx4_release_resource(dev, slave, RES_MPT, 1, 0);
			__mlx4_mpt_release(dev, index);
			break;
		}
		set_param_l(out_param, index);
		break;
	case RES_OP_MAP_ICM:
		index = get_param_l(&in_param);
		id = index & mpt_mask(dev);
		err = mr_res_start_move_to(dev, slave, id,
					   RES_MPT_MAPPED, &mpt);
		if (err)
			return err;

		err = __mlx4_mpt_alloc_icm(dev, mpt->key);
		if (err) {
			res_abort_move(dev, slave, RES_MPT, id);
			return err;
		}

		res_end_move(dev, slave, RES_MPT, id);
		break;
	}
	return err;
}