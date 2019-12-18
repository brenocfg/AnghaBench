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
typedef  int u32 ;
struct mlx5_ib_clock_info {int /*<<< orphan*/  sign; int /*<<< orphan*/  frac; int /*<<< orphan*/  nsec; int /*<<< orphan*/  mult; int /*<<< orphan*/  cycles; } ;
struct TYPE_4__ {int /*<<< orphan*/  frac; int /*<<< orphan*/  nsec; int /*<<< orphan*/  cycle_last; } ;
struct TYPE_3__ {int /*<<< orphan*/  mult; } ;
struct mlx5_clock {TYPE_2__ tc; TYPE_1__ cycles; } ;
struct mlx5_core_dev {struct mlx5_clock clock; struct mlx5_ib_clock_info* clock_info; } ;

/* Variables and functions */
 int MLX5_IB_CLOCK_INFO_KERNEL_UPDATING ; 
 int smp_load_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_store_mb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smp_store_release (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void mlx5_update_clock_info_page(struct mlx5_core_dev *mdev)
{
	struct mlx5_ib_clock_info *clock_info = mdev->clock_info;
	struct mlx5_clock *clock = &mdev->clock;
	u32 sign;

	if (!clock_info)
		return;

	sign = smp_load_acquire(&clock_info->sign);
	smp_store_mb(clock_info->sign,
		     sign | MLX5_IB_CLOCK_INFO_KERNEL_UPDATING);

	clock_info->cycles = clock->tc.cycle_last;
	clock_info->mult   = clock->cycles.mult;
	clock_info->nsec   = clock->tc.nsec;
	clock_info->frac   = clock->tc.frac;

	smp_store_release(&clock_info->sign,
			  sign + MLX5_IB_CLOCK_INFO_KERNEL_UPDATING * 2);
}