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
struct mlx4_mtt {int order; int page_shift; int offset; } ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MLX4_ICM_PAGE_SHIFT ; 
 int mlx4_alloc_mtt_range (struct mlx4_dev*,int) ; 

int mlx4_mtt_init(struct mlx4_dev *dev, int npages, int page_shift,
		  struct mlx4_mtt *mtt)
{
	int i;

	if (!npages) {
		mtt->order      = -1;
		mtt->page_shift = MLX4_ICM_PAGE_SHIFT;
		return 0;
	} else
		mtt->page_shift = page_shift;

	for (mtt->order = 0, i = 1; i < npages; i <<= 1)
		++mtt->order;

	mtt->offset = mlx4_alloc_mtt_range(dev, mtt->order);
	if (mtt->offset == -1)
		return -ENOMEM;

	return 0;
}