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
typedef  int u32 ;
struct mlx5_accel_esp_xfrm {int /*<<< orphan*/  attrs; } ;
struct mlx5_fpga_esp_xfrm {struct mlx5_accel_esp_xfrm accel_xfrm; int /*<<< orphan*/  lock; } ;
struct mlx5_core_dev {int dummy; } ;
struct mlx5_accel_esp_xfrm_attrs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 struct mlx5_accel_esp_xfrm* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MLX5_ACCEL_XFRM_FLAG_REQUIRE_METADATA ; 
 struct mlx5_fpga_esp_xfrm* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct mlx5_accel_esp_xfrm_attrs const*,int) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*) ; 
 scalar_t__ mlx5_fpga_esp_validate_xfrm_attrs (struct mlx5_core_dev*,struct mlx5_accel_esp_xfrm_attrs const*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

struct mlx5_accel_esp_xfrm *
mlx5_fpga_esp_create_xfrm(struct mlx5_core_dev *mdev,
			  const struct mlx5_accel_esp_xfrm_attrs *attrs,
			  u32 flags)
{
	struct mlx5_fpga_esp_xfrm *fpga_xfrm;

	if (!(flags & MLX5_ACCEL_XFRM_FLAG_REQUIRE_METADATA)) {
		mlx5_core_warn(mdev, "Tried to create an esp action without metadata\n");
		return ERR_PTR(-EINVAL);
	}

	if (mlx5_fpga_esp_validate_xfrm_attrs(mdev, attrs)) {
		mlx5_core_warn(mdev, "Tried to create an esp with unsupported attrs\n");
		return ERR_PTR(-EOPNOTSUPP);
	}

	fpga_xfrm = kzalloc(sizeof(*fpga_xfrm), GFP_KERNEL);
	if (!fpga_xfrm)
		return ERR_PTR(-ENOMEM);

	mutex_init(&fpga_xfrm->lock);
	memcpy(&fpga_xfrm->accel_xfrm.attrs, attrs,
	       sizeof(fpga_xfrm->accel_xfrm.attrs));

	return &fpga_xfrm->accel_xfrm;
}