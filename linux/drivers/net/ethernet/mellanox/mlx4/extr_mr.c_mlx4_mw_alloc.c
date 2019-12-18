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
typedef  int u32 ;
struct mlx4_mw {int pd; int type; int /*<<< orphan*/  enabled; int /*<<< orphan*/  key; } ;
struct TYPE_2__ {int flags; int bmme_flags; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
typedef  enum mlx4_mw_type { ____Placeholder_mlx4_mw_type } mlx4_mw_type ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int MLX4_BMME_FLAG_TYPE_2_WIN ; 
 int MLX4_DEV_CAP_FLAG_MEM_WINDOW ; 
 int /*<<< orphan*/  MLX4_MPT_DISABLED ; 
 int MLX4_MW_TYPE_1 ; 
 int MLX4_MW_TYPE_2 ; 
 int /*<<< orphan*/  hw_index_to_key (int) ; 
 int mlx4_mpt_reserve (struct mlx4_dev*) ; 

int mlx4_mw_alloc(struct mlx4_dev *dev, u32 pd, enum mlx4_mw_type type,
		  struct mlx4_mw *mw)
{
	u32 index;

	if ((type == MLX4_MW_TYPE_1 &&
	     !(dev->caps.flags & MLX4_DEV_CAP_FLAG_MEM_WINDOW)) ||
	     (type == MLX4_MW_TYPE_2 &&
	     !(dev->caps.bmme_flags & MLX4_BMME_FLAG_TYPE_2_WIN)))
		return -EOPNOTSUPP;

	index = mlx4_mpt_reserve(dev);
	if (index == -1)
		return -ENOMEM;

	mw->key	    = hw_index_to_key(index);
	mw->pd      = pd;
	mw->type    = type;
	mw->enabled = MLX4_MPT_DISABLED;

	return 0;
}