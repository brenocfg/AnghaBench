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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MLX5_EXTRACT (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_MERGE (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VSC_ADDR_BIT_LEN ; 
 int /*<<< orphan*/  VSC_ADDR_BIT_OFFS ; 
 int /*<<< orphan*/  VSC_ADDR_OFFSET ; 
 int /*<<< orphan*/  VSC_CTRL_OFFSET ; 
 int /*<<< orphan*/  VSC_SIZE_VLD_BIT_LEN ; 
 int /*<<< orphan*/  VSC_SIZE_VLD_BIT_OFFS ; 
 int /*<<< orphan*/  VSC_SPACE_BIT_LEN ; 
 int /*<<< orphan*/  VSC_SPACE_BIT_OFFS ; 
 int /*<<< orphan*/  VSC_STATUS_BIT_LEN ; 
 int /*<<< orphan*/  VSC_STATUS_BIT_OFFS ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*) ; 
 int /*<<< orphan*/  mlx5_vsc_accessible (struct mlx5_core_dev*) ; 
 int vsc_read (struct mlx5_core_dev*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int vsc_write (struct mlx5_core_dev*,int /*<<< orphan*/ ,scalar_t__) ; 

int mlx5_vsc_gw_set_space(struct mlx5_core_dev *dev, u16 space,
			  u32 *ret_space_size)
{
	int ret;
	u32 val = 0;

	if (!mlx5_vsc_accessible(dev))
		return -EINVAL;

	if (ret_space_size)
		*ret_space_size = 0;

	/* Get a unique val */
	ret = vsc_read(dev, VSC_CTRL_OFFSET, &val);
	if (ret)
		goto out;

	/* Try to modify the lock */
	val = MLX5_MERGE(val, space, VSC_SPACE_BIT_OFFS, VSC_SPACE_BIT_LEN);
	ret = vsc_write(dev, VSC_CTRL_OFFSET, val);
	if (ret)
		goto out;

	/* Verify lock was modified */
	ret = vsc_read(dev, VSC_CTRL_OFFSET, &val);
	if (ret)
		goto out;

	if (MLX5_EXTRACT(val, VSC_STATUS_BIT_OFFS, VSC_STATUS_BIT_LEN) == 0)
		return -EINVAL;

	/* Get space max address if indicated by size valid bit */
	if (ret_space_size &&
	    MLX5_EXTRACT(val, VSC_SIZE_VLD_BIT_OFFS, VSC_SIZE_VLD_BIT_LEN)) {
		ret = vsc_read(dev, VSC_ADDR_OFFSET, &val);
		if (ret) {
			mlx5_core_warn(dev, "Failed to get max space size\n");
			goto out;
		}
		*ret_space_size = MLX5_EXTRACT(val, VSC_ADDR_BIT_OFFS,
					       VSC_ADDR_BIT_LEN);
	}
	return 0;

out:
	return ret;
}