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
struct mlx5_ib_pd {int /*<<< orphan*/  pdn; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlx5_ib_pd*) ; 
 int /*<<< orphan*/  mlx5_core_dealloc_pd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 struct mlx5_ib_pd* to_mpd (struct ib_pd*) ; 

__attribute__((used)) static int mlx5_ib_dealloc_pd(struct ib_pd *pd)
{
	struct mlx5_ib_dev *mdev = to_mdev(pd->device);
	struct mlx5_ib_pd *mpd = to_mpd(pd);

	mlx5_core_dealloc_pd(mdev->mdev, mpd->pdn);
	kfree(mpd);

	return 0;
}