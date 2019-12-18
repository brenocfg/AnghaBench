#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  key; } ;
struct mlx5_ib_mw {TYPE_3__ mmkey; } ;
struct mlx5_ib_dev {TYPE_2__* mdev; int /*<<< orphan*/  mr_srcu; } ;
struct ib_mw {int /*<<< orphan*/  device; } ;
struct TYPE_4__ {int /*<<< orphan*/  mkey_table; } ;
struct TYPE_5__ {TYPE_1__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_INFINIBAND_ON_DEMAND_PAGING ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx5_ib_mw*) ; 
 int /*<<< orphan*/  mlx5_base_mkey (int /*<<< orphan*/ ) ; 
 int mlx5_core_destroy_mkey (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  synchronize_srcu (int /*<<< orphan*/ *) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 struct mlx5_ib_mw* to_mmw (struct ib_mw*) ; 
 int /*<<< orphan*/  xa_erase_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int mlx5_ib_dealloc_mw(struct ib_mw *mw)
{
	struct mlx5_ib_dev *dev = to_mdev(mw->device);
	struct mlx5_ib_mw *mmw = to_mmw(mw);
	int err;

	if (IS_ENABLED(CONFIG_INFINIBAND_ON_DEMAND_PAGING)) {
		xa_erase_irq(&dev->mdev->priv.mkey_table,
			     mlx5_base_mkey(mmw->mmkey.key));
		/*
		 * pagefault_single_data_segment() may be accessing mmw under
		 * SRCU if the user bound an ODP MR to this MW.
		 */
		synchronize_srcu(&dev->mr_srcu);
	}

	err = mlx5_core_destroy_mkey(dev->mdev, &mmw->mmkey);
	if (err)
		return err;
	kfree(mmw);
	return 0;
}