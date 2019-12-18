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
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 scalar_t__ MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_UARS_IN_PAGE ; 
 int /*<<< orphan*/  uar_4k ; 

__attribute__((used)) static inline int get_uars_per_sys_page(struct mlx5_ib_dev *dev, bool lib_support)
{
	return lib_support && MLX5_CAP_GEN(dev->mdev, uar_4k) ?
				MLX5_UARS_IN_PAGE : 1;
}