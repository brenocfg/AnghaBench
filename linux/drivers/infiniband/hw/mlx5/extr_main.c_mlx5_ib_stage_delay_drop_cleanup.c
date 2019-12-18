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
struct mlx5_ib_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delay_drop (struct mlx5_ib_dev*) ; 

__attribute__((used)) static void mlx5_ib_stage_delay_drop_cleanup(struct mlx5_ib_dev *dev)
{
	cancel_delay_drop(dev);
}