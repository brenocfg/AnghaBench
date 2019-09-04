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
struct TYPE_2__ {int wq_num; } ;
struct mlx5_pagefault {scalar_t__ event_subtype; int token; int /*<<< orphan*/  type; TYPE_1__ wqe; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 scalar_t__ MLX5_PFAULT_SUBTYPE_WQE ; 
 int mlx5_core_page_fault_resume (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5_ib_err (struct mlx5_ib_dev*,char*,int) ; 

__attribute__((used)) static void mlx5_ib_page_fault_resume(struct mlx5_ib_dev *dev,
				      struct mlx5_pagefault *pfault,
				      int error)
{
	int wq_num = pfault->event_subtype == MLX5_PFAULT_SUBTYPE_WQE ?
		     pfault->wqe.wq_num : pfault->token;
	int ret = mlx5_core_page_fault_resume(dev->mdev,
					      pfault->token,
					      wq_num,
					      pfault->type,
					      error);
	if (ret)
		mlx5_ib_err(dev, "Failed to resolve the page fault on WQ 0x%x\n",
			    wq_num);
}