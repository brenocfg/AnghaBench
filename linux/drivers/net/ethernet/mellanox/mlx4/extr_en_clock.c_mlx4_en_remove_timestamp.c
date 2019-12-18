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
struct mlx4_en_dev {int /*<<< orphan*/ * ptp_clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx4_info (struct mlx4_en_dev*,char*) ; 
 int /*<<< orphan*/  ptp_clock_unregister (int /*<<< orphan*/ *) ; 

void mlx4_en_remove_timestamp(struct mlx4_en_dev *mdev)
{
	if (mdev->ptp_clock) {
		ptp_clock_unregister(mdev->ptp_clock);
		mdev->ptp_clock = NULL;
		mlx4_info(mdev, "removed PHC\n");
	}
}