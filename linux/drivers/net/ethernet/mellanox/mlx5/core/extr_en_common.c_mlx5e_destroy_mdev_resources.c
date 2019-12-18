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
struct TYPE_2__ {int /*<<< orphan*/  tdn; } ;
struct mlx5e_resources {int /*<<< orphan*/  pdn; TYPE_1__ td; int /*<<< orphan*/  mkey; int /*<<< orphan*/  bfreg; } ;
struct mlx5_core_dev {struct mlx5e_resources mlx5e_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct mlx5e_resources*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5_core_dealloc_pd (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_dealloc_transport_domain (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_destroy_mkey (struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_free_bfreg (struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 

void mlx5e_destroy_mdev_resources(struct mlx5_core_dev *mdev)
{
	struct mlx5e_resources *res = &mdev->mlx5e_res;

	mlx5_free_bfreg(mdev, &res->bfreg);
	mlx5_core_destroy_mkey(mdev, &res->mkey);
	mlx5_core_dealloc_transport_domain(mdev, res->td.tdn);
	mlx5_core_dealloc_pd(mdev, res->pdn);
	memset(res, 0, sizeof(*res));
}