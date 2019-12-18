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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MLX5_EXTRACT (unsigned int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  VSC_ADDR_OFFSET ; 
 int /*<<< orphan*/  VSC_DATA_OFFSET ; 
 scalar_t__ VSC_FLAG_BIT_LEN ; 
 scalar_t__ VSC_SYND_BIT_LEN ; 
 int /*<<< orphan*/  VSC_SYND_BIT_OFFS ; 
 int mlx5_vsc_wait_on_flag (struct mlx5_core_dev*,int) ; 
 int vsc_read (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int vsc_write (struct mlx5_core_dev*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int mlx5_vsc_gw_read(struct mlx5_core_dev *dev, unsigned int address,
			    u32 *data)
{
	int ret;

	if (MLX5_EXTRACT(address, VSC_SYND_BIT_OFFS,
			 VSC_FLAG_BIT_LEN + VSC_SYND_BIT_LEN))
		return -EINVAL;

	ret = vsc_write(dev, VSC_ADDR_OFFSET, address);
	if (ret)
		goto out;

	ret = mlx5_vsc_wait_on_flag(dev, 1);
	if (ret)
		goto out;

	ret = vsc_read(dev, VSC_DATA_OFFSET, data);
out:
	return ret;
}