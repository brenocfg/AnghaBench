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
struct mlx5_ib_dev {int num_ports; TYPE_1__* port; int /*<<< orphan*/  mdev; } ;
struct TYPE_4__ {int set_id_valid; int /*<<< orphan*/  set_id; int /*<<< orphan*/  offsets; int /*<<< orphan*/  names; } ;
struct TYPE_3__ {TYPE_2__ cnts; } ;

/* Variables and functions */
 scalar_t__ MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SHARED_RESOURCE_UID ; 
 int __mlx5_ib_alloc_counters (struct mlx5_ib_dev*,TYPE_2__*) ; 
 scalar_t__ is_mdev_switchdev_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_max_uctx ; 
 int mlx5_cmd_alloc_q_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_dealloc_counters (struct mlx5_ib_dev*) ; 
 int /*<<< orphan*/  mlx5_ib_fill_counters (struct mlx5_ib_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*,int,int) ; 

__attribute__((used)) static int mlx5_ib_alloc_counters(struct mlx5_ib_dev *dev)
{
	int num_cnt_ports;
	int err = 0;
	int i;
	bool is_shared;

	is_shared = MLX5_CAP_GEN(dev->mdev, log_max_uctx) != 0;
	num_cnt_ports = is_mdev_switchdev_mode(dev->mdev) ? 1 : dev->num_ports;

	for (i = 0; i < num_cnt_ports; i++) {
		err = __mlx5_ib_alloc_counters(dev, &dev->port[i].cnts);
		if (err)
			goto err_alloc;

		mlx5_ib_fill_counters(dev, dev->port[i].cnts.names,
				      dev->port[i].cnts.offsets);

		err = mlx5_cmd_alloc_q_counter(dev->mdev,
					       &dev->port[i].cnts.set_id,
					       is_shared ?
					       MLX5_SHARED_RESOURCE_UID : 0);
		if (err) {
			mlx5_ib_warn(dev,
				     "couldn't allocate queue counter for port %d, err %d\n",
				     i + 1, err);
			goto err_alloc;
		}
		dev->port[i].cnts.set_id_valid = true;
	}
	return 0;

err_alloc:
	mlx5_ib_dealloc_counters(dev);
	return err;
}