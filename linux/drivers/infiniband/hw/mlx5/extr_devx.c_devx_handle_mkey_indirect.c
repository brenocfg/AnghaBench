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
typedef  int u8 ;
struct mlx5_core_mkey {int key; void* pd; void* size; void* iova; int /*<<< orphan*/  type; } ;
struct mlx5_ib_devx_mr {void* ndescs; struct mlx5_core_mkey mmkey; } ;
struct mlx5_ib_dev {TYPE_2__* mdev; } ;
struct devx_obj {struct mlx5_ib_devx_mr devx_mr; } ;
struct TYPE_3__ {int /*<<< orphan*/  mkey_table; } ;
struct TYPE_4__ {TYPE_1__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 void* MLX5_GET (void*,void*,int /*<<< orphan*/ ) ; 
 void* MLX5_GET64 (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_MKEY_INDIRECT_DEVX ; 
 int /*<<< orphan*/  create_mkey_in ; 
 void* create_mkey_out ; 
 int /*<<< orphan*/  len ; 
 int /*<<< orphan*/  memory_key_mkey_entry ; 
 int /*<<< orphan*/  mkey_7_0 ; 
 int /*<<< orphan*/  mkey_index ; 
 int /*<<< orphan*/  mlx5_base_mkey (int) ; 
 int mlx5_idx_to_mkey (void*) ; 
 int /*<<< orphan*/  pd ; 
 int /*<<< orphan*/  start_addr ; 
 int /*<<< orphan*/  translations_octword_size ; 
 int xa_err (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mlx5_core_mkey*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int devx_handle_mkey_indirect(struct devx_obj *obj,
				     struct mlx5_ib_dev *dev,
				     void *in, void *out)
{
	struct mlx5_ib_devx_mr *devx_mr = &obj->devx_mr;
	struct mlx5_core_mkey *mkey;
	void *mkc;
	u8 key;

	mkey = &devx_mr->mmkey;
	mkc = MLX5_ADDR_OF(create_mkey_in, in, memory_key_mkey_entry);
	key = MLX5_GET(mkc, mkc, mkey_7_0);
	mkey->key = mlx5_idx_to_mkey(
			MLX5_GET(create_mkey_out, out, mkey_index)) | key;
	mkey->type = MLX5_MKEY_INDIRECT_DEVX;
	mkey->iova = MLX5_GET64(mkc, mkc, start_addr);
	mkey->size = MLX5_GET64(mkc, mkc, len);
	mkey->pd = MLX5_GET(mkc, mkc, pd);
	devx_mr->ndescs = MLX5_GET(mkc, mkc, translations_octword_size);

	return xa_err(xa_store(&dev->mdev->priv.mkey_table,
			       mlx5_base_mkey(mkey->key), mkey, GFP_KERNEL));
}