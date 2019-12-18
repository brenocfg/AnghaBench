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
struct mlx5_ib_dev {int /*<<< orphan*/  odp_pf_eq; TYPE_1__ odp_caps; } ;

/* Variables and functions */
 int IB_ODP_SUPPORT ; 
 int /*<<< orphan*/  mlx5_ib_destroy_pf_eq (struct mlx5_ib_dev*,int /*<<< orphan*/ *) ; 

void mlx5_ib_odp_cleanup_one(struct mlx5_ib_dev *dev)
{
	if (!(dev->odp_caps.general_caps & IB_ODP_SUPPORT))
		return;

	mlx5_ib_destroy_pf_eq(dev, &dev->odp_pf_eq);
}