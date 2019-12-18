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
struct mlx5_lag {TYPE_1__* pf; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int mlx5_esw_multipath_prereq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool mlx5_lag_multipath_check_prereq(struct mlx5_lag *ldev)
{
	if (!ldev->pf[0].dev || !ldev->pf[1].dev)
		return false;

	return mlx5_esw_multipath_prereq(ldev->pf[0].dev, ldev->pf[1].dev);
}