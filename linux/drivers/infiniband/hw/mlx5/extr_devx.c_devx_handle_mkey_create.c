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
typedef  int u8 ;
struct mlx5_ib_dev {int dummy; } ;
struct devx_obj {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_INFINIBAND_ON_DEMAND_PAGING ; 
 int /*<<< orphan*/  DEVX_OBJ_FLAGS_INDIRECT_MKEY ; 
 int EINVAL ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int MLX5_BYTE_OFF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_FLD_SZ_BYTES (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_GET (void*,void*,int /*<<< orphan*/ ) ; 
 int MLX5_MKC_ACCESS_MODE_KLMS ; 
 int MLX5_MKC_ACCESS_MODE_KSM ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  access_mode_1_0 ; 
 int /*<<< orphan*/  access_mode_4_2 ; 
 int /*<<< orphan*/  create_mkey_in ; 
 int /*<<< orphan*/  memory_key_mkey_entry ; 
 int /*<<< orphan*/  mkey_umem_valid ; 

__attribute__((used)) static int devx_handle_mkey_create(struct mlx5_ib_dev *dev,
				   struct devx_obj *obj,
				   void *in, int in_len)
{
	int min_len = MLX5_BYTE_OFF(create_mkey_in, memory_key_mkey_entry) +
			MLX5_FLD_SZ_BYTES(create_mkey_in,
			memory_key_mkey_entry);
	void *mkc;
	u8 access_mode;

	if (in_len < min_len)
		return -EINVAL;

	mkc = MLX5_ADDR_OF(create_mkey_in, in, memory_key_mkey_entry);

	access_mode = MLX5_GET(mkc, mkc, access_mode_1_0);
	access_mode |= MLX5_GET(mkc, mkc, access_mode_4_2) << 2;

	if (access_mode == MLX5_MKC_ACCESS_MODE_KLMS ||
		access_mode == MLX5_MKC_ACCESS_MODE_KSM) {
		if (IS_ENABLED(CONFIG_INFINIBAND_ON_DEMAND_PAGING))
			obj->flags |= DEVX_OBJ_FLAGS_INDIRECT_MKEY;
		return 0;
	}

	MLX5_SET(create_mkey_in, in, mkey_umem_valid, 1);
	return 0;
}