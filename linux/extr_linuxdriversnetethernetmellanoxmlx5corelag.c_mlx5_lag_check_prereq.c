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
struct TYPE_2__ {scalar_t__ dev; } ;

/* Variables and functions */
 scalar_t__ mlx5_sriov_is_enabled (scalar_t__) ; 

__attribute__((used)) static bool mlx5_lag_check_prereq(struct mlx5_lag *ldev)
{
	if ((ldev->pf[0].dev && mlx5_sriov_is_enabled(ldev->pf[0].dev)) ||
	    (ldev->pf[1].dev && mlx5_sriov_is_enabled(ldev->pf[1].dev)))
		return false;
	else
		return true;
}