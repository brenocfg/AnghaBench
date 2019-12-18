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
typedef  scalar_t__ u64 ;
struct mlx4_ib_dev {int /*<<< orphan*/ * sl2vl; int /*<<< orphan*/  ib_dev; TYPE_1__* dev; } ;
struct TYPE_4__ {int num_ports; scalar_t__* port_type; } ;
struct TYPE_3__ {TYPE_2__ caps; } ;

/* Variables and functions */
 scalar_t__ MLX4_PORT_TYPE_ETH ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,scalar_t__) ; 
 int mlx4_ib_query_sl2vl (int /*<<< orphan*/ *,int,scalar_t__*) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 

__attribute__((used)) static void mlx4_init_sl2vl_tbl(struct mlx4_ib_dev *mdev)
{
	u64 sl2vl;
	int i;
	int err;

	for (i = 1; i <= mdev->dev->caps.num_ports; i++) {
		if (mdev->dev->caps.port_type[i] == MLX4_PORT_TYPE_ETH)
			continue;
		err = mlx4_ib_query_sl2vl(&mdev->ib_dev, i, &sl2vl);
		if (err) {
			pr_err("Unable to get default sl to vl mapping for port %d.  Using all zeroes (%d)\n",
			       i, err);
			sl2vl = 0;
		}
		atomic64_set(&mdev->sl2vl[i - 1], sl2vl);
	}
}