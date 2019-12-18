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
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  RES_MTT ; 
 int RES_OP_RESERVE_AND_MAP ; 
 int __mlx4_alloc_mtt_range (struct mlx4_dev*,int) ; 
 int /*<<< orphan*/  __mlx4_free_mtt_range (struct mlx4_dev*,int,int) ; 
 int add_res_range (struct mlx4_dev*,int,int,int,int /*<<< orphan*/ ,int) ; 
 int get_param_l (int /*<<< orphan*/ *) ; 
 int mlx4_grant_resource (struct mlx4_dev*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_release_resource (struct mlx4_dev*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_param_l (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mtt_alloc_res(struct mlx4_dev *dev, int slave, int op, int cmd,
			 u64 in_param, u64 *out_param)
{
	int err = -EINVAL;
	int base;
	int order;

	if (op != RES_OP_RESERVE_AND_MAP)
		return err;

	order = get_param_l(&in_param);

	err = mlx4_grant_resource(dev, slave, RES_MTT, 1 << order, 0);
	if (err)
		return err;

	base = __mlx4_alloc_mtt_range(dev, order);
	if (base == -1) {
		mlx4_release_resource(dev, slave, RES_MTT, 1 << order, 0);
		return -ENOMEM;
	}

	err = add_res_range(dev, slave, base, 1, RES_MTT, order);
	if (err) {
		mlx4_release_resource(dev, slave, RES_MTT, 1 << order, 0);
		__mlx4_free_mtt_range(dev, base, order);
	} else {
		set_param_l(out_param, base);
	}

	return err;
}