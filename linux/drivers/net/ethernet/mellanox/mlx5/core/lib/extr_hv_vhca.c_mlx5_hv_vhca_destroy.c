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
struct mlx5_hv_vhca {int /*<<< orphan*/  work_queue; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct mlx5_hv_vhca*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx5_hv_vhca*) ; 

void mlx5_hv_vhca_destroy(struct mlx5_hv_vhca *hv_vhca)
{
	if (IS_ERR_OR_NULL(hv_vhca))
		return;

	destroy_workqueue(hv_vhca->work_queue);
	kfree(hv_vhca);
}