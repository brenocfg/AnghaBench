#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_8__ {int /*<<< orphan*/  length; int /*<<< orphan*/  rkey; int /*<<< orphan*/  lkey; } ;
struct TYPE_5__ {int /*<<< orphan*/  key; } ;
struct mlx5_ib_mr {int npages; int access_flags; TYPE_4__ ibmr; TYPE_1__ mmkey; } ;
struct mlx5_ib_dev {TYPE_3__* mdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  reg_pages; } ;
struct TYPE_7__ {TYPE_2__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void set_mr_fields(struct mlx5_ib_dev *dev, struct mlx5_ib_mr *mr,
			  int npages, u64 length, int access_flags)
{
	mr->npages = npages;
	atomic_add(npages, &dev->mdev->priv.reg_pages);
	mr->ibmr.lkey = mr->mmkey.key;
	mr->ibmr.rkey = mr->mmkey.key;
	mr->ibmr.length = length;
	mr->access_flags = access_flags;
}