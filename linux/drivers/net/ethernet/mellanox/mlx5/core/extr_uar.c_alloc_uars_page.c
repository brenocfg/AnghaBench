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
struct mlx5_uars_page {int bfregs; int fp_avail; int reg_avail; int index; void* reg_bitmap; void* fp_bitmap; int /*<<< orphan*/  ref_count; scalar_t__ map; struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;
typedef  int phys_addr_t ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 struct mlx5_uars_page* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MLX5_BFREGS_PER_UAR ; 
 int MLX5_FP_BFREGS_PER_UAR ; 
 int MLX5_NON_FP_BFREGS_PER_UAR ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  bitmap_free (void*) ; 
 void* bitmap_zalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ioremap (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ioremap_wc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx5_uars_page*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct mlx5_uars_page* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_cmd_alloc_uar (struct mlx5_core_dev*,int*) ; 
 scalar_t__ mlx5_cmd_free_uar (struct mlx5_core_dev*,int) ; 
 int /*<<< orphan*/  mlx5_core_dbg (struct mlx5_core_dev*,char*,int,int) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int) ; 
 int /*<<< orphan*/  set_bit (int,void*) ; 
 int uar2pfn (struct mlx5_core_dev*,int) ; 
 int uars_per_sys_page (struct mlx5_core_dev*) ; 

__attribute__((used)) static struct mlx5_uars_page *alloc_uars_page(struct mlx5_core_dev *mdev,
					      bool map_wc)
{
	struct mlx5_uars_page *up;
	int err = -ENOMEM;
	phys_addr_t pfn;
	int bfregs;
	int i;

	bfregs = uars_per_sys_page(mdev) * MLX5_BFREGS_PER_UAR;
	up = kzalloc(sizeof(*up), GFP_KERNEL);
	if (!up)
		return ERR_PTR(err);

	up->mdev = mdev;
	up->reg_bitmap = bitmap_zalloc(bfregs, GFP_KERNEL);
	if (!up->reg_bitmap)
		goto error1;

	up->fp_bitmap = bitmap_zalloc(bfregs, GFP_KERNEL);
	if (!up->fp_bitmap)
		goto error1;

	for (i = 0; i < bfregs; i++)
		if ((i % MLX5_BFREGS_PER_UAR) < MLX5_NON_FP_BFREGS_PER_UAR)
			set_bit(i, up->reg_bitmap);
		else
			set_bit(i, up->fp_bitmap);

	up->bfregs = bfregs;
	up->fp_avail = bfregs * MLX5_FP_BFREGS_PER_UAR / MLX5_BFREGS_PER_UAR;
	up->reg_avail = bfregs * MLX5_NON_FP_BFREGS_PER_UAR / MLX5_BFREGS_PER_UAR;

	err = mlx5_cmd_alloc_uar(mdev, &up->index);
	if (err) {
		mlx5_core_warn(mdev, "mlx5_cmd_alloc_uar() failed, %d\n", err);
		goto error1;
	}

	pfn = uar2pfn(mdev, up->index);
	if (map_wc) {
		up->map = ioremap_wc(pfn << PAGE_SHIFT, PAGE_SIZE);
		if (!up->map) {
			err = -EAGAIN;
			goto error2;
		}
	} else {
		up->map = ioremap(pfn << PAGE_SHIFT, PAGE_SIZE);
		if (!up->map) {
			err = -ENOMEM;
			goto error2;
		}
	}
	kref_init(&up->ref_count);
	mlx5_core_dbg(mdev, "allocated UAR page: index %d, total bfregs %d\n",
		      up->index, up->bfregs);
	return up;

error2:
	if (mlx5_cmd_free_uar(mdev, up->index))
		mlx5_core_warn(mdev, "failed to free uar index %d\n", up->index);
error1:
	bitmap_free(up->fp_bitmap);
	bitmap_free(up->reg_bitmap);
	kfree(up);
	return ERR_PTR(err);
}