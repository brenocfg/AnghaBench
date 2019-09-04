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
struct mlx5_ib_mw {int /*<<< orphan*/  mmkey; } ;
struct ib_mw {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlx5_ib_mw*) ; 
 int mlx5_core_destroy_mkey (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* to_mdev (int /*<<< orphan*/ ) ; 
 struct mlx5_ib_mw* to_mmw (struct ib_mw*) ; 

int mlx5_ib_dealloc_mw(struct ib_mw *mw)
{
	struct mlx5_ib_mw *mmw = to_mmw(mw);
	int err;

	err =  mlx5_core_destroy_mkey((to_mdev(mw->device))->mdev,
				      &mmw->mmkey);
	if (!err)
		kfree(mmw);
	return err;
}