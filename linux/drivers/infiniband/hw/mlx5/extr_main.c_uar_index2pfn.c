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
struct mlx5_ib_dev {TYPE_1__* mdev; } ;
typedef  int phys_addr_t ;
struct TYPE_2__ {int bar_addr; } ;

/* Variables and functions */
 scalar_t__ MLX5_CAP_GEN (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int MLX5_UARS_IN_PAGE ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  uar_4k ; 

__attribute__((used)) static phys_addr_t uar_index2pfn(struct mlx5_ib_dev *dev,
				 int uar_idx)
{
	int fw_uars_per_page;

	fw_uars_per_page = MLX5_CAP_GEN(dev->mdev, uar_4k) ? MLX5_UARS_IN_PAGE : 1;

	return (dev->mdev->bar_addr >> PAGE_SHIFT) + uar_idx / fw_uars_per_page;
}