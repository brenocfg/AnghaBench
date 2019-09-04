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

/* Variables and functions */
 int /*<<< orphan*/  BIT_ULL (scalar_t__) ; 
 scalar_t__ MLX5_IMR_MTT_BITS ; 
 int /*<<< orphan*/  TASK_SIZE ; 
 scalar_t__ get_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_imr_ksm_entries ; 

int mlx5_ib_odp_init(void)
{
	mlx5_imr_ksm_entries = BIT_ULL(get_order(TASK_SIZE) -
				       MLX5_IMR_MTT_BITS);

	return 0;
}