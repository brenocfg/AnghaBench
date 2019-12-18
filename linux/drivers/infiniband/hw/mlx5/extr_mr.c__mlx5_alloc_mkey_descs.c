#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  key; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int /*<<< orphan*/  rkey; int /*<<< orphan*/  lkey; } ;
struct mlx5_ib_mr {int access_mode; int desc_size; int max_descs; TYPE_2__ mmkey; TYPE_1__ ibmr; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_MKEY_MR ; 
 int mlx5_alloc_priv_descs (int /*<<< orphan*/ ,struct mlx5_ib_mr*,int,int) ; 
 int mlx5_core_create_mkey (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mlx5_free_priv_descs (struct mlx5_ib_mr*) ; 
 int /*<<< orphan*/  mlx5_set_umr_free_mkey (struct ib_pd*,int /*<<< orphan*/ *,int,int,int) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _mlx5_alloc_mkey_descs(struct ib_pd *pd, struct mlx5_ib_mr *mr,
				  int ndescs, int desc_size, int page_shift,
				  int access_mode, u32 *in, int inlen)
{
	struct mlx5_ib_dev *dev = to_mdev(pd->device);
	int err;

	mr->access_mode = access_mode;
	mr->desc_size = desc_size;
	mr->max_descs = ndescs;

	err = mlx5_alloc_priv_descs(pd->device, mr, ndescs, desc_size);
	if (err)
		return err;

	mlx5_set_umr_free_mkey(pd, in, ndescs, access_mode, page_shift);

	err = mlx5_core_create_mkey(dev->mdev, &mr->mmkey, in, inlen);
	if (err)
		goto err_free_descs;

	mr->mmkey.type = MLX5_MKEY_MR;
	mr->ibmr.lkey = mr->mmkey.key;
	mr->ibmr.rkey = mr->mmkey.key;

	return 0;

err_free_descs:
	mlx5_free_priv_descs(mr);
	return err;
}