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
struct TYPE_2__ {void* db_numa_node; void* buf_numa_node; } ;
struct mlx5e_cq_param {TYPE_1__ wq; } ;
struct mlx5e_cq {int dummy; } ;
struct mlx5_core_dev {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 void* dev_to_node (int /*<<< orphan*/ ) ; 
 int mlx5e_alloc_cq_common (struct mlx5_core_dev*,struct mlx5e_cq_param*,struct mlx5e_cq*) ; 

__attribute__((used)) static int mlx5e_alloc_drop_cq(struct mlx5_core_dev *mdev,
			       struct mlx5e_cq *cq,
			       struct mlx5e_cq_param *param)
{
	param->wq.buf_numa_node = dev_to_node(mdev->device);
	param->wq.db_numa_node  = dev_to_node(mdev->device);

	return mlx5e_alloc_cq_common(mdev, param, cq);
}