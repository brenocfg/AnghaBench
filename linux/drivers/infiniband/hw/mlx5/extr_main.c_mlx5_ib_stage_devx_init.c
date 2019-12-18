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
struct mlx5_ib_dev {int devx_whitelist_uid; } ;

/* Variables and functions */
 int mlx5_ib_devx_create (struct mlx5_ib_dev*,int) ; 
 int /*<<< orphan*/  mlx5_ib_devx_init_event_table (struct mlx5_ib_dev*) ; 

__attribute__((used)) static int mlx5_ib_stage_devx_init(struct mlx5_ib_dev *dev)
{
	int uid;

	uid = mlx5_ib_devx_create(dev, false);
	if (uid > 0) {
		dev->devx_whitelist_uid = uid;
		mlx5_ib_devx_init_event_table(dev);
	}

	return 0;
}