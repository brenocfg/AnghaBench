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
struct TYPE_4__ {int /*<<< orphan*/  pin_config; } ;
struct TYPE_3__ {int /*<<< orphan*/  out_work; } ;
struct mlx5_clock {TYPE_2__ ptp_info; int /*<<< orphan*/  overflow_work; TYPE_1__ pps_info; int /*<<< orphan*/ * ptp; int /*<<< orphan*/  pps_nb; } ;
struct mlx5_core_dev {int /*<<< orphan*/ * clock_info; struct mlx5_clock clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_frequency_khz ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_eq_notifier_unregister (struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptp_clock_unregister (int /*<<< orphan*/ *) ; 

void mlx5_cleanup_clock(struct mlx5_core_dev *mdev)
{
	struct mlx5_clock *clock = &mdev->clock;

	if (!MLX5_CAP_GEN(mdev, device_frequency_khz))
		return;

	mlx5_eq_notifier_unregister(mdev, &clock->pps_nb);
	if (clock->ptp) {
		ptp_clock_unregister(clock->ptp);
		clock->ptp = NULL;
	}

	cancel_work_sync(&clock->pps_info.out_work);
	cancel_delayed_work_sync(&clock->overflow_work);

	if (mdev->clock_info) {
		free_page((unsigned long)mdev->clock_info);
		mdev->clock_info = NULL;
	}

	kfree(clock->ptp_info.pin_config);
}