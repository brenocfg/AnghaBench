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
typedef  int u32 ;
struct TYPE_3__ {int crdump_size; } ;
struct TYPE_4__ {TYPE_1__ health; } ;
struct mlx5_core_dev {TYPE_2__ priv; } ;

/* Variables and functions */
 int BAD_ACCESS ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int,int) ; 
 int mlx5_vsc_gw_read_block_fast (struct mlx5_core_dev*,int*,int) ; 

__attribute__((used)) static int mlx5_crdump_fill(struct mlx5_core_dev *dev, u32 *cr_data)
{
	u32 crdump_size = dev->priv.health.crdump_size;
	int i, ret;

	for (i = 0; i < (crdump_size / 4); i++)
		cr_data[i] = BAD_ACCESS;

	ret = mlx5_vsc_gw_read_block_fast(dev, cr_data, crdump_size);
	if (ret <= 0) {
		if (ret == 0)
			return -EIO;
		return ret;
	}

	if (crdump_size != ret) {
		mlx5_core_warn(dev, "failed to read full dump, read %d out of %u\n",
			       ret, crdump_size);
		return -EINVAL;
	}

	return 0;
}