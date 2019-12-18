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
struct mlx5_fc_bulk {scalar_t__ bulk_len; struct mlx5_fc_bulk* bitmask; int /*<<< orphan*/  base_id; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  kfree (struct mlx5_fc_bulk*) ; 
 int /*<<< orphan*/  mlx5_cmd_fc_free (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*) ; 
 scalar_t__ mlx5_fc_bulk_get_free_fcs_amount (struct mlx5_fc_bulk*) ; 

__attribute__((used)) static int
mlx5_fc_bulk_destroy(struct mlx5_core_dev *dev, struct mlx5_fc_bulk *bulk)
{
	if (mlx5_fc_bulk_get_free_fcs_amount(bulk) < bulk->bulk_len) {
		mlx5_core_err(dev, "Freeing bulk before all counters were released\n");
		return -EBUSY;
	}

	mlx5_cmd_fc_free(dev, bulk->base_id);
	kfree(bulk->bitmask);
	kfree(bulk);

	return 0;
}