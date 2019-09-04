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
struct TYPE_2__ {int general_caps; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  null_mkey; int /*<<< orphan*/  mdev; TYPE_1__ odp_caps; } ;

/* Variables and functions */
 int IB_ODP_SUPPORT_IMPLICIT ; 
 int mlx5_cmd_null_mkey (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_ib_err (struct mlx5_ib_dev*,char*,int) ; 

int mlx5_ib_odp_init_one(struct mlx5_ib_dev *dev)
{
	int ret;

	if (dev->odp_caps.general_caps & IB_ODP_SUPPORT_IMPLICIT) {
		ret = mlx5_cmd_null_mkey(dev->mdev, &dev->null_mkey);
		if (ret) {
			mlx5_ib_err(dev, "Error getting null_mkey %d\n", ret);
			return ret;
		}
	}

	return 0;
}