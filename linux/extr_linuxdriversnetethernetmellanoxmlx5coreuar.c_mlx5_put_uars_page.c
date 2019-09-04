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
struct mlx5_uars_page {int /*<<< orphan*/  ref_count; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {TYPE_1__ reg_head; } ;
struct TYPE_6__ {TYPE_2__ bfregs; } ;
struct mlx5_core_dev {TYPE_3__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_rel_func ; 

void mlx5_put_uars_page(struct mlx5_core_dev *mdev, struct mlx5_uars_page *up)
{
	mutex_lock(&mdev->priv.bfregs.reg_head.lock);
	kref_put(&up->ref_count, up_rel_func);
	mutex_unlock(&mdev->priv.bfregs.reg_head.lock);
}