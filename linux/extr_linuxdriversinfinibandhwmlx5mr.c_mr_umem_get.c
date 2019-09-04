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
typedef  int /*<<< orphan*/  u64 ;
struct mlx5_ib_dev {int dummy; } ;
struct ib_umem {int dummy; } ;
struct ib_pd {TYPE_1__* uobject; int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MLX5_MKEY_PAGE_SHIFT_MASK ; 
 int PTR_ERR_OR_ZERO (struct ib_umem*) ; 
 struct ib_umem* ib_umem_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_umem_release (struct ib_umem*) ; 
 int /*<<< orphan*/  mlx5_ib_cont_pages (struct ib_umem*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  mlx5_ib_dbg (struct mlx5_ib_dev*,char*,int,...) ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mr_umem_get(struct ib_pd *pd, u64 start, u64 length,
		       int access_flags, struct ib_umem **umem,
		       int *npages, int *page_shift, int *ncont,
		       int *order)
{
	struct mlx5_ib_dev *dev = to_mdev(pd->device);
	struct ib_umem *u;
	int err;

	*umem = NULL;

	u = ib_umem_get(pd->uobject->context, start, length, access_flags, 0);
	err = PTR_ERR_OR_ZERO(u);
	if (err) {
		mlx5_ib_dbg(dev, "umem get failed (%d)\n", err);
		return err;
	}

	mlx5_ib_cont_pages(u, start, MLX5_MKEY_PAGE_SHIFT_MASK, npages,
			   page_shift, ncont, order);
	if (!*npages) {
		mlx5_ib_warn(dev, "avoid zero region\n");
		ib_umem_release(u);
		return -EINVAL;
	}

	*umem = u;

	mlx5_ib_dbg(dev, "npages %d, ncont %d, order %d, page_shift %d\n",
		    *npages, *ncont, *order, *page_shift);

	return 0;
}