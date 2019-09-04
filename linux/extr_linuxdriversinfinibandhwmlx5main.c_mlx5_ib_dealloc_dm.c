#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct mlx5_memic {TYPE_5__* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  length; } ;
struct mlx5_ib_dm {int dev_addr; TYPE_1__ ibdm; } ;
struct ib_dm {TYPE_2__* uobject; int /*<<< orphan*/  device; } ;
struct TYPE_10__ {int /*<<< orphan*/  pdev; } ;
struct TYPE_9__ {struct mlx5_memic memic; } ;
struct TYPE_8__ {int /*<<< orphan*/  dm_pages; } ;
struct TYPE_7__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_CAP64_DEV_MEM (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_MEMIC_BASE_SIZE ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  bitmap_clear (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx5_ib_dm*) ; 
 int /*<<< orphan*/  memic_bar_start_addr ; 
 int mlx5_cmd_dealloc_memic (struct mlx5_memic*,int,int /*<<< orphan*/ ) ; 
 int pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roundup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* to_mdev (int /*<<< orphan*/ ) ; 
 struct mlx5_ib_dm* to_mdm (struct ib_dm*) ; 
 TYPE_3__* to_mucontext (int /*<<< orphan*/ ) ; 

int mlx5_ib_dealloc_dm(struct ib_dm *ibdm)
{
	struct mlx5_memic *memic = &to_mdev(ibdm->device)->memic;
	struct mlx5_ib_dm *dm = to_mdm(ibdm);
	u64 act_size = roundup(dm->ibdm.length, MLX5_MEMIC_BASE_SIZE);
	u32 page_idx;
	int ret;

	ret = mlx5_cmd_dealloc_memic(memic, dm->dev_addr, act_size);
	if (ret)
		return ret;

	page_idx = (dm->dev_addr - pci_resource_start(memic->dev->pdev, 0) -
		    MLX5_CAP64_DEV_MEM(memic->dev, memic_bar_start_addr)) >>
		    PAGE_SHIFT;
	bitmap_clear(to_mucontext(ibdm->uobject->context)->dm_pages,
		     page_idx,
		     DIV_ROUND_UP(act_size, PAGE_SIZE));

	kfree(dm);

	return 0;
}